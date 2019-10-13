#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void
usage(void)
{
	fprintf(stderr, "usage: rmdir [-p] dir...\n");
}

int
main(int argc, char *argv[])
{
	bool remove_path = false;
	char opt;
	while ((opt = getopt(argc, argv, "p")) != -1) {
		switch (opt) {
		case 'p':
			remove_path = true;
			break;
		default:
			usage();
			return 1;
		}
	}

	if (argc == optind) {
		usage();
		return 1;
	}

	for (int i = optind; i < argc; i++) {
		char *path = argv[i];
		do {
			if (rmdir(path) < 0) {
				perror("rmdir");
				return 1;
			}
		} while (remove_path && strcmp(dirname(path), ".") != 0);
	}

	return 0;
}

