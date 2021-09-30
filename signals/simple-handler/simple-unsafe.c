#include "./../../prepare.h"

#include <signal.h>
#include <time.h>
#include <locale.h>

int _counter = 0;

void unsafeHandler(int sig){

    time_t timet = time(NULL);
    struct tm *ttm = localtime(&timet);
    char _localtimestr[30] = "";
    strftime(_localtimestr, 30, "%X %x", ttm);

    if (sig == SIGINT) // Terminal interrupt
    {
        _counter += 1;
        printf("[%s] %ld SIGINT\n", _localtimestr, getpid());
        return;
    }

    if (sig == SIGTSTP) // Terminal stop.
    {
        _counter += 1;
        printf("[%s] %ld SIGTSTP\n", _localtimestr, getpid());
        exit(EXIT_SUCCESS);
    }

    if (sig == SIGTERM) // Terminate process
    {
        printf("[%s] %ld SIGTERM\n", _localtimestr, getpid());
        exit(EXIT_SUCCESS);
    }

    if (sig == SIGQUIT) // Terminal quit
    {
        printf("[%s] %ld SIGQUIT\n", _localtimestr, getpid());
        exit(EXIT_SUCCESS);
    }

    if (sig == SIGKILL) // Sure kill
    {
        printf("[%s] %ld SIGKILL\n", _localtimestr, getpid());
        exit(EXIT_SUCCESS);
    }

}

int main(int argc, char const *argv[])
{
    // SET TERMINAL SIGNAL HANDLERS
    if (signal(SIGINT,unsafeHandler)==SIG_ERR)
    {
        printf("signal(SIGINT,unsafeHandler) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    if (signal(SIGQUIT,unsafeHandler)==SIG_ERR)
    {
        printf("signal(SIGQUIT,unsafeHandler) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    if (signal(SIGTSTP,unsafeHandler)==SIG_ERR)
    {
        printf("signal(SIGTSTP,unsafeHandler) Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    time_t timet = time(NULL);
    struct tm *ttm = localtime(&timet);
    char _localtimestr[30] = "";
    strftime(_localtimestr, 30, "%X %x", ttm);
    printf("[%s] PROCESS %ld\n", _localtimestr, getpid());

    // CODE
    for (;;)
    {
        getpid();
        sleep(1);
    }

    return 0;
}
