#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
usage(void)
{
	fprintf(stderr, "usage: sleep time\n");
}

int
main(int argc, char *argv[])
{
	unsigned int secs;
	const char *nptr;
	char *endptr = NULL;
	
	if (getopt(argc, argv, "") != -1 || optind != argc - 1) {
		usage();
		return 1;
	}

	errno = 0;
	nptr = argv[1];
	secs = strtol(nptr, &endptr, 10);

	if (nptr == endptr || (errno == 0 && *endptr != 0)){
		fprintf(stderr, "error: invalid number\n");
		return 1;
	} else if (errno != 0) {
		perror("strtol");
		return 1;
	}

	sleep(secs);

	return 0;
}
