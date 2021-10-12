#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <time.h>


char labelTime[50];

char* now_time(){
    time_t now;
    now = time(NULL);
    strftime(labelTime, 50, "%X %Z", localtime(&now));
    return labelTime;
}

int main(int argc, char const *argv[])
{
    printf("[%s] B START PID %d PPID %d\n", now_time(), getpid(), getppid());
    int waiter = 0;

    /*
       <start-program>  BASH
             |
             |
             B ----- C         -- fork 1
             |       |
             |       |
        A----B       C----D    -- fork 2
        |    |       |    |
        |    |       |    |
        A    B       C    D    -- 4 process

    */

    int fork_1 = fork();
    int fork_2 = fork();

    /*
        DO-Process
    */
    if (fork_1==-1) // B PARENT-FORK ERROR
    {
        perror("fork()");
        return EXIT_FAILURE;
    }
    else if (fork_1 == 0) // C CHILD-FORK
    {
        if (fork_2==-1) // C CHILD-FORK-FORK ERROR
        {
            perror("fork()");
            return EXIT_FAILURE;
        }
        else if (fork_2 == 0) // D CHILD-FORK-FORK CHILD
        {
            printf("[%s] D CPID %d PPID %d\n", now_time(), getpid(), getppid());
            sleep(1);
        }
        else // C CHILD-FORK-FORK PARENT
        {
            printf("[%s] C PID %d PPID %d CPID %d\n", now_time(), getpid(), getppid(), fork_2);
            sleep(6);
        }
    }
    else // B PARENT-FORK
    {
        if (fork_2==-1) // B PARENT-FORK-FORK ERROR
        {
            perror("fork()");
            return EXIT_FAILURE;
        }
        else if (fork_2 == 0) // A PARENT-FORK-FORK CHILD
        {
            printf("[%s] A CPID %d PPID %d\n", now_time(), getpid(), getppid());
            sleep(4);
        }
        else // B PARENT-FORK-FORK PARENT
        {
            printf("[%s] B PID %d PPID %d CPID F1 %d F2 %d\n", now_time(), getpid(), getppid(), fork_1, fork_2);
        }
    }


    /*
        WAIT-Process
    */
    if(fork_1 == 0){
        if (fork_2 == 0) // D
        {
            printf("[%s] D CPID %d PPID %d NO-CHILDS-WAITED\n", now_time(), getpid(), getppid());
            sleep(1);
            return 44;
        }
        else // C
        {
            int info_pid1 = 0;
            pid_t waited_pid1 = waitpid(fork_2, &info_pid1, 0);
            printf("[%s] C PID %d PPID %d WAIT-CHILD F2 %d\n", now_time(), getpid(), getppid(), waited_pid1);
            printf("[%s] C STATUS F2 %d :: %d\n", now_time(), waited_pid1, WEXITSTATUS(info_pid1));
            return 33;
        }
    }else{
        if (fork_2 == 0) // A
        {
            printf("[%s] A CPID %d PPID %d NO-CHILDS-WAITED\n", now_time(), getpid(), getppid());
            return 11;
        }
        else // B
        {
            int info_pid1 = 0;
            int info_pid2 = 0;
            pid_t waited_pid2 = waitpid(fork_2, &info_pid2, 0);
            pid_t waited_pid1 = waitpid(fork_1, &info_pid1, 0);
            printf("[%s] B PID %d PPID %d WAIT-CHILD F1 %d F2 %d \n", now_time(), getpid(), getppid(), waited_pid1, waited_pid2);
            printf("[%s] B STATUS F1 %d :: %d\n", now_time(), waited_pid1, WEXITSTATUS(info_pid1));
            printf("[%s] B STATUS F2 %d :: %d\n", now_time(), waited_pid2, WEXITSTATUS(info_pid2));

            return 22;
        }
    }


    return EXIT_SUCCESS;
}
