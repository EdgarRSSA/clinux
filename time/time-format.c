#include "./../prepare.h"
#include <sys/time.h>
#include <time.h>
#include <locale.h>

int main(int argc, char const *argv[],char const *envp[])
{
    //
    // PID
    //
    pid_t PID = getpid();
    printf("Process ID: %ld\n", PID);

    //
    // Time of day
    //

    // get time:
    struct timeval timeofday;
    if (gettimeofday(&timeofday,NULL) == -1)
    {
        printf("gettimeofday(...) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // to local time:
    struct tm *tm = localtime(&timeofday.tv_sec);
    if (tm == NULL)
    {
        printf("localtime(...) Error: %s", strerror(errno));
        return EXIT_FAILURE;
    }

    // apply format:
    int BUF_SIZE = 1000;
    char buf[BUF_SIZE]; /* Nonreentrant */

    // %x -> Date (localized)
    size_t s = strftime(buf, BUF_SIZE, "%x", tm);
    printf("Time of day (strftime) Format [%%x] : %s\n", buf);

    // %X -> Time
    s = strftime(buf, BUF_SIZE, "%X", tm);
    printf("Time of day (strftime) Format [%%X] : %s\n", buf);

    // %Z -> Time Zone
    s = strftime(buf, BUF_SIZE, "%Z", tm);
    printf("Time of day (strftime) Format [%%Z] : %s\n", buf);

    // %B -> Month
    s = strftime(buf, BUF_SIZE, "%B", tm);
    printf("Time of day (strftime) Format [%%B] : %s\n", buf);

    return EXIT_SUCCESS;
}
