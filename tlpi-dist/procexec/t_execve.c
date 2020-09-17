/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 27-1 */

/* t_execve.c

   Demonstrate the use of execve() to execute a program.
   `execve` replaces the currently running program.
*/
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    char *argVec[10];
    char *envVec[] = { "GREET=sault", "BYE=adieu", NULL };

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    /* Create arg list for new program */

    // For `argVec[0]`, want to fetch basename by reverse searching for first
    // `/` and then moving forward one char.
    argVec[0] = strrchr(argv[1], '/');
    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL;

    /* Execute program specified by `argv[1]` */
    execve(argv[1], argVec, envVec);
    errExit("execve"); // If we get here, we messed up.
}
