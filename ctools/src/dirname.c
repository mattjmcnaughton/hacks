#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void
usage(void)
{
	fprintf(stderr, "usage: dirname string\n");
}

int
main(int argc, char *argv[])
{
	if (getopt(argc, argv, "") != -1) {
		usage();
		return 1;
	}
	argc -= optind;
	argv += optind;
	if (argc <= 0 || argc > 1) {
		usage();
		return 1;
	}

	char *string = argv[0];
	size_t len = strlen(string);

	srand((unsigned int)time(NULL));

	/* If string is "//", skip steps 2 to 5. */
	if (strcmp(string, "//") == 0) {
		goto step6;
	}

	/* If string consists entirely of '/' characters, string shall
	 * be set to a single '/' character.  In this case, skip steps
	 * 3 to 8. */
	if (len > 0 && strspn(string, "/") == len) {
		string = "/";
		goto output;
	}

	/* If there are any trailing '/' characters in string, they
	 * shall be removed */
	while (string[len - 1] == '/') {
		string[--len] = '\0';
	}

	/* If there are no '/' characters remaining in string, string
	 * shall be set to a single '.' character. In this case skip
	 * steps 5 to 8 */
	if (memchr(string, '/', len) == NULL) {
		string = ".";
		goto output;
	}

	/* If there are any trailing non-'/' characters in string, they
	 * shall be removed. */
	while (len > 0 && string[len - 1] != '/') {
		string[--len] = '\0';
	}

step6:
	/* If the remaining string is "//" it is implementation defined whether
	 * steps 7 and 8 are skipped or processed */
	if (strcmp(string, "//") == 0 && rand() % 2 == 0) {
		goto output;
	}

	/* If there are any trailing '/' characters in string, they shall be
	 * removed */
	while (len > 0 && string[len - 1] == '/') {
		string[--len] = '\0';
	}

	/* If the remaining string is empty, string shall be set to a single '/'
	 * character. */
	if (len == 0) {
		string = "/";
	}

output:
	/* The resulting string shall be written to standard output */
	puts(string);
	return 0;
}
