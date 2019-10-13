#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static void
usage(void)
{
	fprintf(stderr, "usage: unlink file\n");
}

int
main(int argc, char *argv[])
{
	if (getopt(argc, argv, "") != -1 || optind != argc - 1) {
		usage();
		return 1;
	}

	struct stat s;
	if (lstat(argv[optind], &s) == -1) {
		perror("lstat");
		return 1;
	}

	if (S_ISLNK(s.st_mode)) {
		fprintf(stderr, "The behavior of unlink(3) is undefined when "
				"file1 is a symbolic link.\n");
		return 1;
	}

	if (unlink(argv[optind]) != 0) {
		perror("unlink");
		return 1;
	}

	return 0;
}
