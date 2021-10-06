#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <time.h>

#include "Headers.h"

int main(int argc, char const *argv[])
{
    int waiter = 0;
    int el = time(NULL);
    int el2 = 0;
    printf("PID: %d [0:%d]\n", getpid(), el);

    int fork_1 = fork();
    int fork_2 = fork();

    if (fork_1 == 0 ){

        // CHILD
        sleep(2);
        el2 = time(NULL);
        printf("PID: %d  PPID: %d [%d]\n", getpid(), getppid(), el2 - el);

        if (fork_2 == 0 ){

            // CHILD
            sleep(2);
            el2 = time(NULL);
            printf("PID: %d  PPID: %d [%d]\n", getpid(), getppid(), el2 - el);

            waiter = wait(NULL);
            if (waiter == -1)
            {
                printf("CHILD: %d PARENT: %d\n", getpid(), getppid());
            }
            else
            {
                printf("PARENT: %d WAIT: %d\n", getpid(), waiter);
            }

        }else{

            //PARENT
            el2 = time(NULL);
            printf("PID: %d  PPID: %d CHILD[%d] [%d]\n", getpid(), getppid(), fork_1, el2 - el);


            waiter = wait(NULL);
            if (waiter == -1)
            {
                printf("CHILD: %d PARENT: %d\n", getpid(), getppid());
            }
            else
            {
                printf("PARENT: %d WAIT: %d\n", getpid(), waiter);
            }
        }

    }else{

        //PARENT
        el2 = time(NULL);
        printf("PID: %d  PPID: %d CHILD[%d] [%d]\n", getpid(), getppid(), fork_1, el2 - el);

        waiter = wait(NULL);
        if (waiter == -1)
        {
            printf("CHILD: %d PARENT: %d\n", getpid(), getppid());
        }
        else
        {
            printf("PARENT: %d WAIT: %d\n", getpid(), waiter);
        }

    }






    return EXIT_SUCCESS;
}
