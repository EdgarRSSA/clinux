#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>

extern char **environ;

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
        //CHILD EXECV
        printf("%d %d Before-Execv\n", getpid(), getppid());


        int envcounter = 0;
        printf("%d %d Enviroment: \n", getpid(), getppid());
        while (environ[envcounter]!=NULL)
        {
            printf("%d %d \t%s\n", getpid(), getppid(), environ[envcounter]);
            envcounter++;
        }


        /*
            EXECV

            The execv function executes the file named by filename as a new process image.

            The argv argument is an array of null-terminated strings that is used to provide a
            value for the argv argument to the main function of the program to be executed. The
            last element of this array must be a null pointer. By convention, the first element
            of this array is the file name of the program sans directory names.

            The environment for the new process image is taken from the environ variable of
            the current process image.
        */
        char *args[2] = {"\0", NULL};
        printf("%d %d execv /usr/bin/whoami \n", getpid(), getppid());

        fflush(stderr);
        fflush(stdout);
        // EXECV
        int e_code = execv("/usr/bin/whoami", args);

        // EXECV RETURN HERE ONLY IF THE 'EXECV' CALL IS INCORRECT.
        if (e_code == -1)
        {
            perror("execv(...)");
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
