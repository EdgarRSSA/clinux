#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int callback(){
    printf("%d : CALLBACK\n", getpid());
    return 66;
}


int main(int argc, char const *argv[])
{
    printf("%d : Callback and fork program:\n", getpid());

    pid_t child = fork();
    if (child == -1)
    {
        perror("fork()");
        return EXIT_FAILURE;
    }
    else if (child == 0) // CHILD CODE
    {
        exit(callback()); // CALLBACK
    }
    else // PARENT CODE
    {
        int child_status = 0;
        if (waitpid(child, &child_status, 0) == 1)
        {
            perror("waitpid(child, NULL, 0)");
            return EXIT_FAILURE;
        }

        printf("%d : CHILD STATUS : %d\n", getpid(), WEXITSTATUS(child_status));
        return EXIT_SUCCESS;
    }



}
