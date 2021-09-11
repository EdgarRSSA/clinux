#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char const *argv[])
{

    printf("File IO\n");

    // OPEN
    int file1 = open("./text.example.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    /*
          ^       ^        ^            ^               ^
          |       |        |            |               |
          FD     call     path      flag create      File Permissions
    */

    // Manage Errors
    if (file1 == -1)
    {
        printf("Open file: %s",strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("File IO Open: OK\n");

    close(file1);

    return EXIT_SUCCESS;
}
