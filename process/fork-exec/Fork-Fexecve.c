#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <wait.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/fcntl.h>

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
        //CHILD
        printf("%d %d Before-Execv\n", getpid(), getppid());

        // CHILD ENVIRONTMENT
        printf("%d %d Enviroment: %s\n", getpid(), getppid(),getenv("PATH"));

        /*
            FEXECVE

            This is similar to execv, but permits you to specify the environment for the
            new program explicitly as the env argument. This should be an array of strings
            in the same format as for the environ variable.
        */

        // FEXECVE Arguments:
        char *e_argv[] = {"/bin/bash\0","-c\0","echo $(printenv)\0", NULL};

        // FEXECVE ENVIRONTMENT:
        char *e_envv[] = {"PATH=.:/usr/bin\0", NULL};

        // FEXECV fd open
        int e_fd = open("/bin/bash", __O_PATH);
        if (e_fd == -1)
        {
            perror("open(...)");
            fflush(stderr);
            fflush(stdout);
            _exit(errno);
        }
        printf("%d %d (Open) /bin/bash [%d]\n", getpid(), getppid(), e_fd);
        fflush(stderr);
        fflush(stdout);

        // FEXECVE:
        int e_code = fexecve(e_fd, e_argv, e_envv);


        // FEXECVE RETURN HERE ONLY IF THE 'FEXECVE' CALL IS INCORRECT.
        if (e_code == -1)
        {
            perror("fexecve(...)");

            // FEXECV fd close
            if (close(e_fd) == -1)
            {
                perror("close(...)");
                fflush(stderr);
                fflush(stdout);
                _exit(errno);
            }

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
