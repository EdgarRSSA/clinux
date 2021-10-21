#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <threads.h>
#include <sys/types.h>

/**
*  @param arg Args.
*/
int child_func(void *arg)
{
    struct timespec sleeptime;
    sleeptime.tv_sec = 1;
    if (thrd_sleep(&sleeptime, NULL)!=0){
        thrd_exit(EXIT_FAILURE);
    }
    char **args = arg;
    printf("%ld %ld CHILD\n", (long)getpid(), (unsigned long)thrd_current());
    printf("%ld %ld ARG0 :%s\n", (long)getpid(), (unsigned long)thrd_current(), args[0]);

    return EXIT_SUCCESS;
}

/**
 *  Threads.
 * @param argc Argument Counter.
 * @param argv Argument Array.
 * @param envp Environment Array.
 *
*/
int main (int argc, char *argv[], char *envp[])
{
    printf("%ld %ld MAIN :D\n", (long)getpid(), (unsigned long)thrd_current());

    /**
    *	Child Thread.
    */
    thrd_t child_thread;
    char *child_argv[] = {(char *)argv[0], (char *)NULL};
    thrd_create(&child_thread, (thrd_start_t)child_func, (void *)child_argv);

    printf("%ld %ld Created : %ld\n", (long)getpid(), (unsigned long)thrd_current(), (unsigned long)child_thread);

    /**
    *	Wait for child.
    */
    int child_status;
    thrd_join(child_thread, &child_status);

    printf("%ld %ld Status Child : %d\n", (long)getpid(), (unsigned long)thrd_current(), child_status);

    return EXIT_SUCCESS;
}
