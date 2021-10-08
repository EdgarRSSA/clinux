#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>


int main (int argc, char *argv[], char *envp[])
{

    printf("%d %d MESSAGE 1\n", getpid(), getppid());

    fflush(stdout); // Flush Before fork.
    pid_t child = fork();

    printf("%d %d MESSAGE 2\n", getpid(), getppid());

    if (child==-1)
    {
        perror("fork()");
        return EXIT_FAILURE;
    }
    else if (child==0) // child
    {
        printf("%d %d MESSAGE 3\n", getpid(), getppid());

        fflush(stdout);      // Flush Messages Before BIG TASK (sleep).
        sleep(1); // Heavy task simulation.

        printf("%d %d MESSAGE 4\n", getpid(), getppid());

        fflush(stdout);      // Flush Messages Before _exit.
        _exit(EXIT_SUCCESS); // exit WITHOUT call to handlers.
    }
    else // parent
    {
        printf("%d %d MESSAGE 3\n", getpid(), getppid()); // Message Before waits.

        fflush(stdout); // Flush to stdout.
        waitpid(child, NULL, 0); // waitpid child.

        printf("%d %d MESSAGE 4\n", getpid(), getppid()); // Message after waits.


        exit(EXIT_SUCCESS); //  exit calling handlers. (auto-fflush)

    }

}
