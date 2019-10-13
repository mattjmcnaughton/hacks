#include <stdio.h>
#include <unistd.h>

static void
usage(void)
{
	fprintf(stderr, "usage: logname\n");
}

int
main(int argc, char *argv[])
{
	while (getopt(argc, argv, "") != -1) {
		usage();
		return 1;
	}

	if (argc != optind) {
		usage();
		return 1;
	}

	char *name = getlogin();
	if (!name) {
		perror("getlogin");
		return 1;
	}
	printf("%s\n", name);
	return 0;
}
