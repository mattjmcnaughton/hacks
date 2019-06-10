/* mem_segments.c

   A program that does nothing in particular, but the comments indicate
   which memory segments each type of variable is allocated in.
*/
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536]; /* Uninitialized data segment */
int primes[] = { 2, 3, 5, 7 }; /* Initialized data segment */

// `static` indicates func is static (i.e. only visible throughout the file)
static int
square(int x) // x is allocated in stack frame for square
{
    int result; // Allocated in stack frame for square

    result = x * x;
    return result; // Return value passed via register
}

static void
doCalc(int val) // val is allocated in stack frame for doCalc
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t; // t is allocated in stack frame for doCalc

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char *argv[])
{
    static int key = 9973; // key is an initialized data segment
    static char mbuf[10240000]; // uninitialized data segment
    char *p;

    p = malloc(1024); // pointer to memory allocated in heap segment

    doCalc(key);

    exit(EXIT_SUCCESS);
}
