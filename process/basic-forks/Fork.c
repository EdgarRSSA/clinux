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
             B ----- C         -- fork 1
             |       |
             |       |
             B       C         -- 2 process
    */

    int fork_1 = fork();

    /*
        DO-Process
    */
    if (fork_1==-1) // Error
    {
        perror("fork()");
        return EXIT_FAILURE;
    }
    else if (fork_1 == 0) // C
    {
        printf("[%s] C CPID %d PPID %d\n", now_time(), getpid(), getppid());
        sleep(1);
    }
    else // B
    {
        printf("[%s] B PID %d PPID %d CPID %d\n", now_time(), getpid(), getppid(), fork_1);
    }


    /*
        WAIT-Process
    */
    if (fork_1 == 0) // C
    {
        printf("[%s] C CPID %d PPID %d NO-CHILDS-WAITED\n", now_time(), getpid(), getppid());
        return 111;
    }
    else // B
    {
        int info_pid = 0;
        pid_t waited_pid = waitpid(fork_1, &info_pid, 0);
        printf("[%s] B PID %d PPID %d WAIT-CHILD %d\n", now_time(), getpid(), getppid(), waited_pid);
        printf("[%s] B STATUS F1 %d :: %d\n", now_time(), waited_pid, WEXITSTATUS(info_pid));
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
