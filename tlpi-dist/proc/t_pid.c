#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    pid_t pid, ppid;

    pid = getpid();
    ppid = getppid();

    printf("Pid: %d, Ppid: %d\n", pid, ppid);
}
