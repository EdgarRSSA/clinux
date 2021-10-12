#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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

    printlog("START");

    /*
       <start-program>  BASH
             |
             |
             B ----- C         -- fork 1
             |       |
             |       |
    A--------B       C--------D    -- fork 2
    |        |       |        |
    |        |       |        |
    A---E    B---F   C---G    D----H    -- fork 3
    |   |    |   |   |   |    |    |
    |   |    |   |   |   |    |    |
    A   E    B   F   C   G    D    H    -- 8 process (2^n)


    */

    int fork_1 = fork();
    int fork_2 = fork();
    int fork_3 = fork();


    /*
        IF:PROCESS - DO SPECIFIC ACTION:
    */

    if (fork_1 == -1) // Error F1
    {
        perror("fork()-1");
        return EXIT_FAILURE;
    }
    else if (fork_1 == 0) // CHILD F1
    {
        if (fork_2 == -1) // Error F2
        {
            perror("fork()-2");
            return EXIT_FAILURE;
        }
        else if (fork_2 == 0) // CHILD F2
        {
            if (fork_3 == -1) // Error F3
            {
                perror("fork()-3");
                return EXIT_FAILURE;
            }
            else if (fork_3 == 0) // CHILD F3
            {
                // H
                printlog("H");
                sleep(1);
            }
            else // PARENT F3
            {
                // D
                printlog("D");
            }
        }
        else // PARENT F2
        {
            if (fork_3 == -1) // Error F3
            {
                perror("fork()-3");
                return EXIT_FAILURE;
            }
            else if (fork_3 == 0) // CHILD F3
            {
                // G
                printlog("G");
            }
            else // PARENT F3
            {
                // C
                printlog("C");
            }
        }
    }
    else // PARENT F1
    {
        if (fork_2 == -1) // Error F2
        {
            perror("fork()-2");
            return EXIT_FAILURE;
        }
        else if (fork_2 == 0) // CHILD F2
        {
            if (fork_3 == -1) // Error F3
            {
                perror("fork()-3");
                return EXIT_FAILURE;
            }
            else if (fork_3 == 0) // CHILD F3
            {
                // E
                printlog("E");
            }
            else // PARENT F3
            {
                // A
                printlog("A");
            }
        }
        else // PARENT F2
        {
            if (fork_3 == -1) // Error F3
            {
                perror("fork()-3");
                return EXIT_FAILURE;
            }
            else if (fork_3 == 0) // CHILD F3
            {
                // F
                printlog("F");
            }
            else // PARENT F3
            {
                // B
                printlog("B");
            }
        }
    }

    /*
        ALL DO:
    */
    printlog("ALL-PRINT-THIS");

    /*
        WAIT-STEP
    */
    if (fork_1 == 0) // CHILD F1
    {
        if (fork_2 == 0) // CHILD F2
        {
            if (fork_3 == 0) // CHILD F3
            {
                // H
                printlog("H NOT-WAITS");
            }
            else // PARENT F3
            {
                // D
                waitpid(fork_3, NULL, 0);
                printlog("D WAITS H");
            }
        }
        else // PARENT F2
        {
            if (fork_3 == 0) // CHILD F3
            {
                // G
                printlog("G NOT-WAITS");
            }
            else // PARENT F3
            {
                // C
                waitpid(fork_3, NULL, 0);
                waitpid(fork_2, NULL, 0);
                printlog("C WAITS D,G");
            }
        }
    }
    else // PARENT F1
    {
        if (fork_2 == 0) // CHILD F2
        {
            if (fork_3 == 0) // CHILD F3
            {
                // E
                printlog("E NOT-WAITS");
            }
            else // PARENT F3
            {
                // A
                waitpid(fork_3, NULL, 0);
                printlog("A WAITS E");
            }
        }
        else // PARENT F2
        {
            if (fork_3 == 0) // CHILD F3
            {
                // F
                printlog("F NOT-WAITS");
            }
            else // PARENT F3
            {
                // B
                waitpid(fork_3, NULL, 0);
                waitpid(fork_2, NULL, 0);
                waitpid(fork_1, NULL, 0);
                printlog("B WAITS C,A,F");
            }
        }
    }

    return EXIT_SUCCESS;
}
