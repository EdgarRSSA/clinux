#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/times.h>
#include <time.h>
#include <sys/resource.h>

int main (int argc, char *argv[], char *envp[])
{

    struct rusage stat;
    clock_t elap1 = times(NULL);

    printf("Resources Usage\n");

    for (size_t i = 0; i < 10000; i++)
    {
        getpid();
        getppid();
        getuid();
        getgid();

    }
    sleep(1);

    clock_t elap2 = times(NULL);
    long clkt_sec = sysconf(_SC_CLK_TCK);
    getrusage(RUSAGE_SELF, &stat);

    printf("User time %ld s %10f s\n", stat.ru_utime.tv_sec, (double) stat.ru_utime.tv_usec / 1000000);
    printf("System time %ld s %10f s\n", stat.ru_stime.tv_sec, (double) stat.ru_stime.tv_usec / 1000000);
    printf("Elapsed time %10f s\n", ((double)elap2 - elap1) / clkt_sec);

    return EXIT_SUCCESS;
}
