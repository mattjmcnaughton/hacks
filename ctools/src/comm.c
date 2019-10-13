#include <assert.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

enum display_mode {
	LINES_LEFT = 1 << 0,
	LINES_RIGHT = 1 << 1,
	LINES_BOTH = 1 << 2,
};

static void
usage(void)
{
	fprintf(stderr, "usage: comm [-123] file1 file2\n");
}

static int
clamp(int n, int min, int max)
{
	return n < min ? min : n > max ? max : n;
}

static const char *
leadfor(int diff, unsigned int display_mode)
{
	const unsigned int leftright = LINES_LEFT | LINES_RIGHT;
	switch (diff) {
	case 0:
		if ((display_mode & leftright) == leftright) {
			return "\t\t";
		} else if ((display_mode & leftright)) {
			return "\t";
		}
		return "";
	case 1:
		return (display_mode & LINES_LEFT) ?  "\t" : "";
	case -1:
		/* fallthrough */
	default:
		assert(false);
	}
}

int
main(int argc, char *argv[])
{
	unsigned int display_mode =
		LINES_LEFT | LINES_RIGHT | LINES_BOTH;

	char c;
	while ((c = getopt(argc, argv, "123")) != -1) {
		switch (c) {
		case '1':
			display_mode &= ~LINES_LEFT;
			break;
		case '2':
			display_mode &= ~LINES_RIGHT;
			break;
		case '3':
			display_mode &= ~LINES_BOTH;
			break;
		}
	}

	if (argc - optind != 2) {
		usage();
		return 1;
	}

	FILE *f[2] = { 0 };
	char *names[2];
	names[0] = argv[optind], names[1] = argv[optind + 1];
	if (names[0][0] == '-' && names[0][1] == '\0') {
		f[0] = stdin;
	}
	if (names[1][0] == '-' && names[1][1] == '\0') {
		f[1] = stdin;
	}

	if (f[0] == stdin && f[1] == stdin) {
		fprintf(stderr, "comm: behavior is unspecified when "
				"both inputs are stdin\n");
		return 1;
	}

	if (strcmp(names[0], names[1]) == 0) {
		struct stat st;
		if (stat(names[0], &st) != 0) {
			perror(names[0]);
		}
		if (S_ISBLK(st.st_mode) || S_ISCHR(st.st_mode)
				|| S_ISFIFO(st.st_mode)) {
			fprintf(stderr, "comm: behavior is unspecified when "
					"both inputs are the same special "
					"file\n");
			return 1;
		}
	}

	if (!f[0] && (f[0] = fopen(names[0], "r")) == NULL) {
		perror(names[0]);
		return 1;
	}
	if (!f[1] && (f[1] = fopen(names[1], "r")) == NULL) {
		perror(names[1]);
		return 1;
	}

	int ret = 0, diff = 0;
	char *lp[2] = { 0 }, *_lp[2] = { 0 };
	size_t sz[2] = { 0 };

	while (true) {
		for (int i = 0; i < 2; ++i) {
			if ((diff != 0 && i == (diff < 0)) || feof(f[i])) {
				/* Processing unique lines */
				continue;
			}
			if (lp[i]) {
				free(_lp[i]);
				_lp[i] = strdup(lp[i]);
			}
			if (getline(&lp[i], &sz[i], f[i]) > 0) {
				if (_lp[i] && strcmp(_lp[i], lp[i]) > 0) {
					fprintf(stderr, "Error: the behavior "
							"of this utility is "
							"unspecified for "
							"unsorted files.\n");
					ret = 1;
					goto cleanup;
				}
				continue;
			}
			/* Error occured */
			if (ferror(f[i])) {
				ret = 1;
				perror(names[i]);
				goto cleanup;
			} else if (!feof(f[!i])) {
				lp[i] = NULL;
				continue;
			} else if (feof(f[i])) {
				goto cleanup;
			}
		}

		if (lp[0] == NULL) {
			diff = 1;
		} else if (lp[1] == NULL) {
			diff = -1;
		} else {
			diff = strcmp(lp[0], lp[1]);
			diff = clamp(diff, -1, 1);
		}

		switch (diff) {
		case -1:
			if ((display_mode & LINES_LEFT)) {
				printf("%s", lp[0]);
			}
			break;
		case 0:
			if ((display_mode & LINES_BOTH)) {
				printf("%s%s", leadfor(
					diff, display_mode), lp[0]);
			}
			break;
		case 1:
			if ((display_mode & LINES_RIGHT)) {
				printf("%s%s", leadfor(
					diff, display_mode), lp[1]);
			}
			break;
		}
	}

cleanup:
	for (int i = 0; i < 2; ++i) {
		fclose(f[i]);
		free(lp[i]);
		free(_lp[i]);
	}
	return ret;
}
