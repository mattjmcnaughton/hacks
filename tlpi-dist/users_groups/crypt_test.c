#define _XOPEN_SOURCE
#include <unistd.h>
#include "tlpi_hdr.h"

/**
 * Program demonstrating how `crypt` library by default only authenticates
 * against the first 8 chars.
 */

int
main(int argc, char *argv[])
{
    char *passwd1, *passwd2;

    passwd1 = crypt("hi-everyone111", "1a");
    passwd2 = crypt("hi-everyone222", "1a");

    printf("%s", passwd1);
    printf("%s", passwd2);
}
