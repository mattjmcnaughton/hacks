#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
usage(void)
{
	fprintf(stderr, "usage: nice [-n increment] utility [argument...]\n");
}

int
main(int argc, char *argv[])
{
	int increment = 10;

	char opt;
	while ((opt = getopt(argc, argv, "n:")) != -1) {
		switch (opt) {
		case 'n': {
			char *endptr = NULL;
			long value = strtol(optarg, &endptr, 10);
			if (value < INT_MIN || value > INT_MAX
			    		|| *endptr != '\0') {
				fprintf(stderr,
					"nice: invalid increment value '%s'\n",
					optarg);
				return 1;
			}
			increment = (int)value;
			break;
		}
		default:
			  usage();
			  return 1;
		}
	}

	if (optind == argc) {
		usage();
		return 1;
	}

#ifdef _XOPEN_SOURCE
	if (nice(increment) == -1) {
		perror("nice");
	}
#else
	fprintf(stderr, "nice: compiled without XSI support; no-op\n");
#endif

	if (execvp(argv[optind], argv + optind) == -1) {
		perror("execvp");
		return 1;
	}

	return 0;
}
