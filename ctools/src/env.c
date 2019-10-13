#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

static void
usage(void)
{
	fputs("env [-i] [name=value]... [utility [argument...]]\n", stderr);
}

int
main(int argc, char *argv[])
{
	if (argc > 1 && strcmp(argv[1], "-") == 0) {
		usage();
		return 1;
	}

	char opt;
	bool clear = false;
	while ((opt = getopt(argc, argv, "i")) != -1) {
		switch (opt) {
		case 'i':
			clear = true;
			break;
		default:
			usage();
			return 1;
		}
	}

	if (clear) {
		environ = NULL;
	}

	argc = argc - optind;
	argv = &argv[optind];

	int cmd_idx = 0;
	for (; cmd_idx < argc; cmd_idx++) {
		if (!strchr(argv[cmd_idx], '=')) {
			break;
		}
	}

	for (int i = 0; i < cmd_idx; i++) {
		if (putenv(argv[i]) != 0) {
			perror("env");
			return 1;
		}
	}

	/* No command, print the env */
	if (cmd_idx == argc) {
		for (int i = 0; environ[i]; i++) {
			puts(environ[i]);
		}
		return 0;
	}

	argv = &argv[cmd_idx];

	execvp(argv[0], argv);

	/* if exec returns, it's errored */
	fprintf(stderr, "env: '%s': %s\n", argv[0], strerror(errno));
	switch (errno) {
	case ENOENT:
		return 127;
	default:
		return 126;
	}
}
