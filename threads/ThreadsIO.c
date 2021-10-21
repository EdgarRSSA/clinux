#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <threads.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE

/**
 * Test function, NOT Thread safely.
*  @param arg Args.
*/
int child_func(void *arg)
{
    printf("PID %ld THREAD %ld TAG %s\n", (long)getpid(), (unsigned long)thrd_current(), (char *)arg);
    fflush(stdout);
    return EXIT_SUCCESS;
}

/**
 *  Threads UNSTABLE IO.
 * @param argc Argument Counter.
 * @param argv Argument Array.
 * @param envp Environment Array.
 *
*/
int main (int argc, char *argv[], char *envp[])
{
    fork();
    printf("PID %ld THREAD %ld TAG TH00/MAIN\n", (long)getpid(), (unsigned long)thrd_current());
    fflush(stdout);
    /**
    *	Childs Threads.
    */
    int NUMTHREADS = 30;
    thrd_t child_thread[NUMTHREADS];
    int th_created[NUMTHREADS];
    const char *child_label[] = {
        "TH01",
        "TH02",
        "TH03",
        "TH04",
        "TH05",
        "TH06",
        "TH07",
        "TH08",
        "TH09",
        "TH10",
        "TH11",
        "TH12",
        "TH13",
        "TH14",
        "TH15",
        "TH16",
        "TH17",
        "TH18",
        "TH19",
        "TH20",
        "TH21",
        "TH22",
        "TH23",
        "TH24",
        "TH25",
        "TH26",
        "TH27",
        "TH28",
        "TH29",
        "TH30",
    };

    //printf("TAG LIST TEST:\n");
    //for (size_t i = 0; i < NUMTHREADS; i++)
    //{
    //    printf("%ld:%s ", i, child_label[i]);
    //}
    //printf("---\n");

    for (size_t i = 0; i < NUMTHREADS; i++)
    {
        char *alfa = (char *)child_label[i];
        th_created[i] = thrd_create(&child_thread[i], (thrd_start_t)child_func, (void *)alfa);

        if (thrd_success == th_created[i])
        {
            printf("PID %ld THREAD %ld CREATE %ld TAG %s\n", (long)getpid(), (unsigned long)thrd_current(), (unsigned long)child_thread[i], child_label[i]);
        }
        else if (thrd_error ==th_created[i])
        {
            printf("PID %ld THREAD %ld CREATE ERROR TAG %s\n", (long)getpid(), (unsigned long)thrd_current(), child_label[i]);
        }
        else if (thrd_nomem ==th_created[i])
        {
            printf("PID %ld THREAD %ld CREATE NOMEMORY TAG %s\n", (long)getpid(), (unsigned long)thrd_current(), child_label[i]);
        }
        fflush(stdout);
    }


    /**
    *	Wait for child.
    */


    int child_status[NUMTHREADS];
    for (size_t i = 0; i < NUMTHREADS; i++)
    {
        if (thrd_join(child_thread[i], &child_status[i])==thrd_error)
        {
            printf("PID %ld THREAD %ld JOIN %ld ERROR TAG%s\n", (long)getpid(), (unsigned long)thrd_current(), (unsigned long)child_thread[i], child_label[i]);
        }
        else
        {
            printf("PID %ld THREAD %ld JOIN %ld JOINED %s STATUS %d\n", (long)getpid(), (unsigned long)thrd_current(), (unsigned long)child_thread[i], (char *)child_label[i], (int)child_status[i]);
        }
        fflush(stdout);

    }



    return EXIT_SUCCESS;
}
