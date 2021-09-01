#include <errno.h> // Error Codes
#include <stdio.h> // Print to stdout
#include <string.h> // Convert errno to str
#include <sys/file.h> // Include the Open call
#include <stdlib.h> // Exit call and EXIT_FAILURE Flag
#include <unistd.h> // Close call

#include<sys/types.h>

int main(){

    char *path_file = "./Dockerfile";
    printf("Manejo de Errores\n");

    // Open file call:
    int file_fd = open(path_file,O_RDONLY);

    if (file_fd == -1)
    {
        // Manage error for open call:
        //printf("Open(...) Error: %s\n",strerror(errno));
        perror("Open(...) Error");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Open Success:
        printf("Open [%s] FD: %d\n",path_file,file_fd);

        if (close(file_fd)==-1){

            // Manage error for close call
            perror("Close(...) Error:");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Close Success:
            printf("Close [%s] FD: %d\n",path_file,file_fd);

        }

    }
    char *ccc_c = "END\n";
    write(STDOUT_FILENO, ccc_c,strlen(ccc_c));
    exit(EXIT_SUCCESS);
}
