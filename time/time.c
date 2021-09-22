#include "./../prepare.h"
#include <sys/time.h>
#include <time.h>

int main(int argc, char const *argv[],char const *envp[])
{
    //
    // PID
    //
    pid_t PID = getpid();
    printf("Info about Process ID: %ld\n", PID);

    //
    // Time of day
    //
    struct timeval timeofday;
    struct timezone timeofdayzone; // OBSOLETE

    if (gettimeofday(&timeofday,NULL) == -1)
    {
        printf("gettimeofday(...) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Time of day (gettimeofday): %ld s %ld ms\n", timeofday.tv_sec,timeofday.tv_usec);

    //
    // Time of day (old)
    //
    time_t timeofday2 = time(NULL);

    if ( timeofday2 == -1)
    {
        printf("time(...) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Time of day (time): %ld s\n", timeofday2);

    //
    // Printable form of time, include \0 y \n
    //
    time_t time2char = timeofday.tv_sec;
    char *timelabel = ctime(&time2char);
    if (timelabel == NULL)
    {
        printf("ctime(...) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Time of day (ctime): %s\n", timelabel);

    //
    // GMTime
    //
    struct tm *gmtlabel = gmtime(&timeofday.tv_sec);
    if (gmtlabel == NULL)
    {
        printf("gmtime(...) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Time of day (gmtime): zone:%s year:%u week-day:%u month-day:%u year-day:%u month:%u hour:%u minute:%u second:%u \n",
        gmtlabel->tm_zone,
        (gmtlabel->tm_year + 1900),
        gmtlabel->tm_wday,
        gmtlabel->tm_mday,
        gmtlabel->tm_yday,
        (gmtlabel->tm_mon + 1),
        gmtlabel->tm_hour,
        gmtlabel->tm_min,
        gmtlabel->tm_sec
        );

    return EXIT_SUCCESS;
}
