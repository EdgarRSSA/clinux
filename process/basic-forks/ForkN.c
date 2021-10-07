#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

#include <time.h>



char labelTime[50];

// return time.
char* now_time(){
    time_t now;
    now = time(NULL);
    strftime(labelTime, 50, "%X %Z", localtime(&now));
    return labelTime;
}

// Print a log info.
void printlog(char* message){
    printf("[%s] PPID %6d PID %6d : %s\n", now_time(), getppid(), getpid(), message);
}

// Fork3
int main(int argc, char const *argv[])
{
    // ONLY STARTUP
    printlog("START");
    char *types_fork[] = {"error", "CPID", "PID"};
    printf("\n%6s %6s %6s %6s\n\n", "fork4", "fork3", "fork2", "fork1");
    int code = 1;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                for (size_t l = 0; l < 3; l++)
                {
                    printf("%6s %6s %6s %6s %d\n", types_fork[i], types_fork[j], types_fork[k], types_fork[l], code);
                    code += 1;
                }
            }
        }
    }

    //
    // FORKSx4
    //
    int iforks[4] = {fork(), fork(), fork(), fork()};
    char *forks[4];




    // Comparadores
    for (size_t i = 0; i < 4; i++)
    {
        if (iforks[i]==-1)
        {
            forks[i] = types_fork[0];
        }
        else if (iforks[i]==0)
        {
            forks[i] = types_fork[1];
        }
        else
        {
            forks[i] = types_fork[2];
        }

    }


    // RUN IN C-P-P-P
    bool flag = (strcmp("CPID", forks[0]) == 0) && (strcmp("PID", forks[1]) == 0) && (strcmp("PID", forks[2]) == 0) && (strcmp("PID", forks[3]) == 0);
    if (flag)
    {
        printlog("PRINCIPAL FIRST CHILD");
    }

    // RUN IN P-C-P-P
    flag = (strcmp("PID", forks[0]) == 0) && (strcmp("CPID", forks[1]) == 0) && (strcmp("PID", forks[2]) == 0) && (strcmp("PID", forks[3]) == 0);
    if (flag)
    {
        printlog("PRINCIPAL SECOND CHILD");
    }

    // RUN IN P-P-C-P
    flag = (strcmp("PID", forks[0]) == 0) && (strcmp("PID", forks[1]) == 0) && (strcmp("CPID", forks[2]) == 0) && (strcmp("PID", forks[3]) == 0);
    if (flag)
    {
        printlog("PRINCIPAL THIRD CHILD");
    }

    // RUN IN P-P-P-C
    flag = (strcmp("PID", forks[0]) == 0) && (strcmp("PID", forks[1]) == 0) && (strcmp("PID", forks[2]) == 0) && (strcmp("CPID", forks[3]) == 0);
    if (flag)
    {
        printlog("PRINCIPAL FOURTH CHILD");
    }

    // RUN IN P-P-P-P
    flag = (strcmp("PID", forks[0]) == 0) && (strcmp("PID", forks[1]) == 0) && (strcmp("PID", forks[2]) == 0) && (strcmp("PID", forks[3]) == 0);
    if (flag)
    {
        waitpid(iforks[0], NULL, 0);
        waitpid(iforks[1], NULL, 0);
        waitpid(iforks[2], NULL, 0);
        waitpid(iforks[3], NULL, 0);
        printlog("PRINCIPAL");
    }
    return EXIT_SUCCESS;
}
