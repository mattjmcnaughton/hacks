/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 18-1 */

/* t_unlink.c

    Demonstrate that, when a file is unlinked, it is not actually removed from
    the file system until after any open descriptors referring to it are closed.

    Usage: t_unlink file
*/
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int
main(int argc, char *argv[])
{
    int fd, j, numBlocks;
    char shellCmd[CMD_SIZE]; // Command to be passed to `system()`
    char buf[BUF_SIZE]; // Random bytes to write to the file.

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s temp-file [num-1kB-blocks] \n", argv[0]);

    numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kB-blocks")
                           : 100000;

    // Use O_EXCL to ensure we create a new file... i.e. call will fail if the
    // file exists.
    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    // Remove file name... won't be deleted until the file descriptor is closed.
    if (unlink(argv[1]) == -1)
        errExit("unlink");

    for (j = 0; j < numBlocks; j++) {
        // Write lots of junk to the file.
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            fatal("partial/failed write");
    }

    // Write formatted output to sized buffer.
    snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    // run the shell cmd
    system(shellCmd);

    if (close(fd) == -1)
        errExit("close");
    printf("***** Closed file descriptor\n");

    system(shellCmd);
    exit(EXIT_SUCCESS);
}
