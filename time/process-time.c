#include "./../prepare.h"
#include <sys/times.h>
#include <time.h>

void printcputime(){

    clock_t cputimes;
    struct tms cputms;
    cputimes = times(&cputms);

    if (cputimes == -1)
    {
        printf("times(...) Error:%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /*  Time used by the program so far (user time + system time).
        The result / CLOCKS_PER_SEC is program time in seconds.  */
    clock_t cpu_realtime = clock();
    if (cpu_realtime == -1)
    {
        printf("clock(...) Error:%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Cpu Real Time (clock): %ld clock-ticks [%.2f ms]\n", cpu_realtime, (double) cpu_realtime*1000 / CLOCKS_PER_SEC);

    long clkticks = sysconf(_SC_CLK_TCK);
    printf("Clock ticks per second : %ld clock-ticks/sec\n", clkticks);

    printf("Cpu User Time: %.2f ms\n", (double) cputms.tms_utime*1000 / clkticks);
    printf("Cpu System Time: %.2f ms\n", (double) cputms.tms_stime*1000 / clkticks);
    printf("Cpu Children-User Time: %.2f ms\n", (double) cputms.tms_cutime*1000 / clkticks);
    printf("Cpu Children-System Time: %.2f ms\n", (double) cputms.tms_cstime*1000 / clkticks);

}


int main(int argc, char const *argv[],char const *envp[])
{
    //
    // PID
    //
    pid_t PID = getpid();
    printf("Process ID: %ld\n", PID);

    // Start Loop.
    printf("Start Loop.\n");
    printcputime();

    // Loop of api-syscalls to kernel.
    for (size_t i = 0; i < 1000000; i++)
    {
        getppid();
        getpid();
        getuid();
        getgid();
    }

    // End loop.
    printf("\nEnd Loop.\n");
    printcputime();

    return EXIT_SUCCESS;
}
