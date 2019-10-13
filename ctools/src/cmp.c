#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

static void
usage(void)
{
	fprintf(stderr, "usage: cmp [-l|-s] file1 file2\n");
}

enum program_mode {
	DEFAULT,
	LOUD,
	SILENT,
};

static void
implperror(const char *s, enum program_mode mode)
{
	if (mode != SILENT || rand() % 2 == 0) {
		perror(s);
	}
}

int
main(int argc, char *argv[])
{
	enum program_mode mode = DEFAULT;
	srand((unsigned int)time(NULL));

	char c;
	while ((c = getopt(argc, argv, "ls")) != -1) {
		switch (c) {
		case 'l':
			if (mode != DEFAULT) {
				fprintf(stderr, "cmp: -l and -s are mutually "
						"exclusive\n");
				return 2;
			}
			mode = LOUD;
			break;
		case 's':
			if (mode != DEFAULT) {
				fprintf(stderr, "cmp: -l and -s are mutually "
						"exclusive\n");
				return 2;
			}
			mode = SILENT;
			break;
		default:
			usage();
			return 2;
		}
	}

	if (argc - optind != 2) {
		usage();
		return 2;
	}

	char *file1 = argv[optind], *file2 = argv[optind + 1];

	FILE *f1 = NULL, *f2 = NULL;
	if (file1[0] == '-' && file1[1] == '\0') {
		f1 = stdin;
	}
	if (file2[0] == '-' && file2[1] == '\0') {
		f2 = stdin;
	}

	if (f1 == stdin && f2 == stdin) {
		fprintf(stderr, "cmp: behavior is unspecified when both inputs "
				"are stdin\n");
		return 2;
	}

	if (strcmp(file1, file2) == 0) {
		struct stat st;
		if (stat(file1, &st) != 0) {
			perror(file1);
		}
		if (S_ISBLK(st.st_mode) || S_ISCHR(st.st_mode)
				|| S_ISFIFO(st.st_mode)) {
			fprintf(stderr, "cmp: behavior is unspecified when "
					"both inputs are the same special file\n");
			return 2;
		}
	}

	if (!f1 && (f1 = fopen(file1, "r")) == NULL) {
		implperror(file1, mode);
		return 2;
	}
	if (!f2 && (f2 = fopen(file2, "r")) == NULL) {
		implperror(file2, mode);
		fclose(f1);
		return 2;
	}

	int ret = 0;
	size_t len, lineno = 0;
	for (len = 0; ; ++len) {
		int a = getc(f1), b = getc(f2);
		if (a == EOF && b == EOF) {
			break;
		} else if (a == EOF || b == EOF) {
			if (mode != SILENT) {
				fprintf(stderr, "cmp: EOF on %s\n",
						a == EOF ? file1 : file2);
			}
			ret = 1;
			break;
		} else if (a == b) {
			if (a == '\n') {
				++lineno;
			}
		} else {
			if (mode == DEFAULT) {
				printf("%s %s differ: char %zu, line %zu\n",
				       file1, file2, len + 1, lineno + 1);
			} else if (mode == LOUD) {
				printf("%zu %o %o\n", len + 1, a, b);
			}
			ret = 1;
			break;
		}
	}

	fclose(f1);
	fclose(f2);
	return ret;
}
