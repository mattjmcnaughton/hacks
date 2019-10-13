#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	if (getopt(argc, argv, "") != -1 || optind != argc) {
		fprintf(stderr, "usage: tty\n");
		return 2;
	}

	char *name = ttyname(STDIN_FILENO);
	if (!name) {
		if (errno == ENOTTY) {
			printf("not a tty\n");
			return 1;
		}
		perror("ttyname");
		return 2;
	}

	printf("%s\n", name);
	return 0;
}
