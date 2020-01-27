/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 26-1 */

/* multi_wait.c

   Demonstrate the use of wait(2): create multiple children and then wait
   for them all.

   Usage: multi_wait sleep-time...

   One child process is created for each command-line argument. Each child
   sleeps for the number of seconds specified in the corresponding command-line
   argument before exiting. After all children have been created, the parent
   loops, waiting for terminated children, and displaying their PIDs.
*/
#include <sys/wait.h>
#include <time.h>
#include "curr_time.h"              /* Declaration of currTime() */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int numDead; // Number of children so far waited for
    pid_t childPid; // PID of waited for child
    int j;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s sleep-time...\n", argv[0]);

    setbuf(stdout, NULL);

    for (j = 1; j < argc; j++) {
        switch (fork()) {
        case -1:
            errExit("fork");

        case 0:
            printf("[%s] child %d started with PID %ld, sleeping %s "
                   "seconds\n", currTime("%T"), j, (long) getpid(), argv[j]);
            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
            _exit(EXIT_SUCCESS);

        default: // Parent exits the loop
            break;
        }
    }

    numDead = 0;
    for (;;) { // Parent waits for each child to exit.
        childPid = wait(NULL); // wait will block until a child exits or there are no children
        if (childPid == -1) { // -1 means either no more children or error - use errno
            if (errno == ECHILD) {
                printf("No more children - bye!\n");
                exit(EXIT_SUCCESS);
            } else {
                errExit("wait");
            }
        }

        numDead++;
        printf("[%s] wait() returned child PID %ld (numDead=%d)\n",
                currTime("%T"), (long) childPid, numDead);

    }
}
