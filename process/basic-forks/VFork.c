#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>


pid_t CHILD_VFORK; // Shared.
char *text_shared; // Shared.

char label[30]; // Shared (used for processinfo).

// Proccess info.
char* processinfo ()
{
    sprintf(label, "%5d <= %5d", getpid(), getppid());
    return label;
}

// Child VFORKED process (CALLBACK).
int child_func ()
{
    CHILD_VFORK = getpid();
    printf("%s CHILD_VFORK:%d\n", processinfo(), CHILD_VFORK);
    text_shared = "ABCDWERTG234231";
    printf("%s Text: %s\n", processinfo(), text_shared);
    sleep(1);
    printf("%s End sleep\n", processinfo());
    return EXIT_SUCCESS;
}

// Parent entry point.
int main (int argc, char *argv[], char *envp[])
{

    char *localshared = "PARENT";
    printf("%s Start.\n", processinfo());
    printf("%s LABEL SHARED: %s.\n", processinfo(), localshared);

    pid_t child = vfork(); // VFORK AND WAIT.

    printf("%s After VFORK.\n", processinfo());

    if (child == -1)
    {
        perror("vfork()");
    }
    else if (child==0) // CHILD
    {
        localshared = "CHILD";
        printf("%s LABEL SHARED: %s.\n", processinfo(), localshared);
        exit(child_func());
    }
    else // PARENT
    {
        printf("%s CHILD_VFORK SHARED: %d.\n", processinfo(), CHILD_VFORK);
        printf("%s TEXT SHARED: %s.\n", processinfo(), text_shared);
        printf("%s LABEL SHARED: %s.\n", processinfo(), localshared);
        return EXIT_SUCCESS;
    }
}
