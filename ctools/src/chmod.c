#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

static void
usage(void)
{
	fprintf(stderr, "usage: chmod [-R] mode file...\n");
}

enum mode_operation {
	MODE_SET, /* chmod 777 */
	MODE_ADD, /* chmod a+rwx */
	MODE_REM, /* chmod a-rwx */
	MODE_CLR, /* chmod a=rwx */
};

static int
process(enum mode_operation op, mode_t desired, const char *path,
		bool recursive, bool all_x)
{
	struct stat s;
	if (stat(path, &s) < 0) {
		perror(path);
		return 1;
	}
	mode_t prev = s.st_mode, mode = desired;
	if (all_x && (S_ISDIR(s.st_mode) || (prev & 0111) != 0)) {
		mode |= 0111; /* Set all execute bits */
	}
	const mode_t suid_mask = S_ISGID | S_ISUID;
	switch (op) {
	case MODE_SET:
		/* This space deliberately left blank */
		break;
	case MODE_ADD:
		/* Requests to set the set-user-ID-on-execution or
		 * set-group-ID-on-execution bit when all execute bits are
		 * currently clear and none are being set are ignored. */
		if ((mode & S_ISGID) || (mode & S_ISUID)) {
			if (!((prev | mode) & 0111)) {
				mode &= ~suid_mask;
			}
		}
		mode = prev | mode;
		break;
	case MODE_REM:
		mode = prev ^ (mode & prev);
		break;
	case MODE_CLR:
		mode = prev & ~mode;
		break;
	}

	/* Implementation defined behavior: */
	bool r = rand() % 2 == 0;
	if (r && S_ISREG(s.st_mode) && op != MODE_SET && !(mode & 0111)) {
		/* (symbolic mode, regular files) Requests to clear all execute
		 * bits also clear the set-user-ID-on-execution and
		 * set-group-ID-on-execution bits. Requests to clear the
		 * set-user-ID-on-execution or set-group-ID-on-execution bits
		 * when all execute bits are currently clear are ignored. */
		if ((prev & 0111)) {
			mode &= ~suid_mask;
		} else if (!(mode & suid_mask)
				&& (mode & suid_mask) != (prev & suid_mask)) {
			/* However, if the command ls -l file writes an s in the
			 * position indicating that the set-user-ID-on-execution
			 * or set-group-ID-on-execution is set, the commands
			 * chmod u-s file or chmod g-s file, respectively, shall
			 * not be ignored. */
			if (mode == MODE_REM && (desired == S_ISGID
						|| desired == S_ISUID)) {
				mode &= ~suid_mask;
				mode |= prev & suid_mask;
			}
		}
	} else if (r && !S_ISREG(s.st_mode)) {
		mode &= ~suid_mask;
	}

	if (chmod(path, mode) < 0) {
		perror(path);
		return 1;
	}

	if (recursive && S_ISDIR(s.st_mode)) {
		DIR *dir = opendir(path);
		if (!dir) {
			perror(path);
			return 1;
		}
		errno = 0;
		struct dirent *dirent;
		char subpath[PATH_MAX + 1];
		while ((dirent = readdir(dir))) {
			if (strcmp(dirent->d_name, ".") == 0
					|| strcmp(dirent->d_name, "..") == 0) {
				continue;
			}
			size_t plen = strlen(path);
			assert(plen + strlen(dirent->d_name) + 1 < PATH_MAX);
			strcpy(subpath, path);
			if (subpath[plen - 1] != '/') {
				strcat(subpath, "/");
			}
			strcat(subpath, dirent->d_name);
			if (process(op, mode, subpath, recursive, all_x) != 0) {
				return 1;
			}
		}
		if (errno != 0) {
			perror(path);
			return 1;
		}
	}

	return 0;
}

static int
symbolic_mode(char *sym, mode_t *mode, enum mode_operation *op, bool *all_x)
{
	mode_t who = 0, what = 0;
	int i;
	for (i = 0; sym[i]; ++i) {
		bool other = false;
		switch (sym[i]) {
		case 'u':
			who |= 0007;
			break;
		case 'g':
			who |= 0070;
			break;
		case 'o':
			who |= 0700;
			break;
		case 'a':
			who |= 0777;
			break;
		default:
			other = true;
			break;
		}
		if (other) {
			switch (sym[i]) {
			case '+':
				*op = MODE_ADD;
				if (who == 0) {
					who = 0777;
				}
				break;
			case '-':
				*op = MODE_REM;
				if (who == 0) {
					who = 0777;
				}
				break;
			case '=':
				*op = MODE_CLR;
				if (who == 0) {
					who = 0777;
				}
				break;
			default:
				goto error;
			}
			break;
		}
	}

	for (++i; sym[i]; ++i) {
		switch (sym[i]) {
		case 'x':
			what |= 0111 & who;
			break;
		case 'w':
			what |= 0222 & who;
			break;
		case 'r':
			what |= 0444 & who;
			break;
		case 's':
			if ((who & 0070)) {
				what |= S_ISGID;
			} else if ((who & 0007)) {
				what |= S_ISUID;
			}
			break;
#ifdef _XOPEN_SOURCE
		case 't':
			what |= S_ISVTX;
			break;
#endif
		case 'X':
			*all_x = true;
			break;
		default:
			goto error;
		}
	}

	*mode = what;
	return 0;

error:
	fprintf(stderr, "chmod: invalid symbolic mode '%s'\n", sym);
	return 1;
}

int
main(int argc, char *argv[])
{
	bool recursive = false, all_x = false;
	srand((unsigned int)time(NULL));

	char c;
	while ((c = getopt(argc, argv, "R")) != -1) {
		switch (c) {
		case 'R':
			recursive = true;
			break;
		default:
			usage();
			return 1;
		}
	}

	if (optind + 1 >= argc) {
		usage();
		return 1;
	}

	mode_t mode;
	enum mode_operation op = MODE_SET;

	errno = 0;
	char *end;
	long int l = strtol(argv[optind], &end, 8);
	unsigned long int ul = (unsigned long int)l;

	if (!end[0] && errno == 0) {
		if ((ul & ~07777) > 0 || l < 0) {
			fprintf(stderr, "chmod: %s is an invalid mode\n",
					argv[optind]);
			return 1;
		}
		mode = (mode_t)ul;
		op = MODE_SET;
	} else {
		if (symbolic_mode(argv[optind], &mode, &op, &all_x) != 0) {
			return 1;
		}
	}

	for (int i = optind + 1; i < argc; ++i) {
		if (process(op, mode, argv[i], recursive, all_x) != 0) {
			return 1;
		}
	}

	return 0;
}
