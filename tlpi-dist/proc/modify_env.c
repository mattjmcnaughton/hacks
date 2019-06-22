/* Listing 6-4 */

/* modify_env.c

   Demonstrate modification of the process environment list.

   Usage: modify_env name=value...

   Note: some UNIX implementations do not provide clearenv(), setenv(),
   and unsetenv().
*/
#define _GNU_SOURCE /* Get various declarations from <stdlib.h> */
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int
main(int argc, char *argv[])
{
    int j;
    char **ep;

    clearenv(); // Erase entire environment

    // Add any definitions specified on the command line.
    for (j = 1; j < argc; j++)
        if (putenv(argv[j]) != 0)
            errExit("putenv: %s", argv[j]);

    // Add a definition for GREET if one doesn't already exist
    if (setenv("GREET", "Hello world", 0) == -1)
        errExit("setenv");

    // Remove any existing definition of BYE
    unsetenv("BYE");

    // Display current environment
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}
