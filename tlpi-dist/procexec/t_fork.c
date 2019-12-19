/* Listing 24-1 */

/* t_fork.c

   Demonstrate the use of fork(), showing that parent and child
   get separate copies of stack and data segments.
*/
#include "tlpi_hdr.h"

static int idata = 111; // Allocated in data segment

int
main(int argc, char *argv[])
{
    int istack = 222; // stack allocated
    pid_t childPid;

    switch (childPid = fork()) {
    case -1:
        errExit("fork");

    // only child
    case 0:
        idata *= 3;
        istack *= 3;
        break;

    // only parent
    default:
        sleep(10);
        break;
    }

    // both parent and child
    printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(),
            (childPid == 0) ? "(child) " : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}
