/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 15-5 */

/* t_umask.c

   Demonstrate the affect of umask() in conjunction with open() and mkdir().
*/
#include <sys/stat.h>
#include <fcntl.h>
#include "file_perms.h"
#include "tlpi_hdr.h"

#define MYFILE "myfile"
#define MYDIR "mydir"
// Ask for rw-rw----
#define FILE_PERMS    (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
// Ask for rwxrwxrwx
#define DIR_PERMS     (S_IRWXU | S_IRWXG | S_IRWXO)
// By default, group and other can not write or execute (i.e. deny ----wx-wx)
#define UMASK_SETTING (S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH)

int
main(int argc, char *argv[])
{
    int fd;
    struct stat sb;
    mode_t u;

    // System call to set the umask for the process.
    umask(UMASK_SETTING);

    // Open file for read/write, create if doesn't exist, and fail if pathname
    // already exists.
    fd = open(MYFILE, O_RDWR | O_CREAT | O_EXCL, FILE_PERMS);
    if (fd == -1)
        errExit("open-%s", MYFILE);
    if (mkdir(MYDIR, DIR_PERMS) == -1)
        errExit("mkdir-%s", MYDIR);

    // Retrieve and clear the umask.
    u = umask(0);

    if (stat(MYFILE, &sb) == -1)
        errExit("stat-%s", MYFILE);
    printf("Requested file perms: %s\n", filePermStr(FILE_PERMS, 0));
    printf("Process umask: %s\n", filePermStr(u, 0));
    // `sb.st_mode` gives the permissions for the file.
    printf("Actual file perms: %s\n", filePermStr(sb.st_mode, 0));

    if (stat(MYDIR, &sb) == -1)
        errExit("stat-%s", MYDIR);
    printf("Requested dir perms: %s\n", filePermStr(DIR_PERMS, 0));
    printf("Process umask: %s\n", filePermStr(u, 0));
    // `sb.st_mode` gives the permissions for the dir.
    printf("Actual dir perms: %s\n", filePermStr(sb.st_mode, 0));

    // Delete file
    if (unlink(MYFILE) == -1)
        errMsg("unline-%s", MYFILE);
    if (rmdir(MYDIR) == -1)
        errMsg("rmdir-%s", MYDIR);
    exit(EXIT_SUCCESS);
}
