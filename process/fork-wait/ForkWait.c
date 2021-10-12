#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>

int childCallback ()
{
    sleep(1);
    printf("%5d %5d Child.\n", getpid(),getppid());
    fflush(stdout);
    for (size_t i = 0; i < 1000; i++)
    {
        getpid();
        getppid();
        getuid();
        getgid();
    }
    return 66;
}

int main (int argc, char *argv[], char *envp[])
{


    printf("%5d %5d Wait.\n", getpid(), getppid());
    fflush(stdout);

    pid_t child = fork();
    if (child==-1)
    {
        perror("fork()");
        return EXIT_FAILURE;
    }
    else if (child==0)
    {
        _exit(childCallback());
    }
    else
    {
        int stats;
        struct rusage childUsage;

        wait4(child, &stats, 0, &childUsage);

        printf("Child: %d Exit code: %d\n", child, WEXITSTATUS(stats));
        printf("Child System Time : %ld s %10f s\n", (long) childUsage.ru_stime.tv_sec, (double) childUsage.ru_stime.tv_usec / 1000000);
        printf("Child User Time : %ld s %10f s\n", (long) childUsage.ru_utime.tv_sec, (double) childUsage.ru_utime.tv_usec / 1000000);

        struct rusage ru;
        getrusage(RUSAGE_SELF, &ru);
        printf("Parent System Time : %ld s %10f s\n", (long) ru.ru_stime.tv_sec, (double) ru.ru_stime.tv_usec / 1000000);
        printf("Parent User Time : %ld s %10f s\n", (long) ru.ru_utime.tv_sec, (double) ru.ru_utime.tv_usec / 1000000);

        return EXIT_SUCCESS;
    }
}
