#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>

int main (int argc, char *argv[], char *envp[])
{
    printf("%d %d Before Fork\n", getpid(), getppid());
    fflush(stdout);


    int child = fork();

    if (child==-1)
    {
        perror("fork()");
        return EXIT_FAILURE;
    }
    else if (child==0)
    {
        //CHILD EXECL
        printf("%d %d Before-Execv\n", getpid(), getppid());

        printf("%d %d Enviroment: %s\n", getpid(), getppid(),getenv("PATH"));

        /*
            EXECL

            This is similar to execv, but the argv strings are specified individually instead
            of as an array. A null pointer must be passed as the last such argument.
        */
        fflush(stderr);
        fflush(stdout);

        // EXECL
        int e_code = execl("/usr/bin/whoami", "\0", NULL);


        // EXECL RETURN HERE ONLY IF THE 'EXEC' CALL IS INCORRECT.
        if (e_code == -1)
        {
            perror("execl(...)");
            fflush(stderr);
            fflush(stdout);
            _exit(errno);
        }

    }
    else
    {
        int child_status;
        waitpid(child, &child_status, 0);
        printf("%d %d Wait Child %d Status Code %d\n", getpid(), getppid(), child, child_status);
        return EXIT_SUCCESS;
    }

}
