#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// MY DEFS
#define WRITE_BUFF_BYTES 1024 // 1KB

int main(int argc, char const *argv[])
{
    // OPEN
    char *file1_path = "./text.txt";
    int file1 = open(file1_path, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (file1 == -1) // Errors
    {
        printf("Open file: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Open file: %s\n", file1_path);

    // WRITE
    char *file1_buffer = "ABCDEF1234567890!#$&¿?=)(/+}]{[-_";
    int file1_write = write(file1, file1_buffer, strlen(file1_buffer));
    if (file1_write == -1) // Errors
    {
        printf("Write file: %s\n",strerror(errno));
        close(file1);
        exit(EXIT_FAILURE);
    }

    printf("Content Write:%d\n\t%s\n", file1_write,file1_buffer);
    close(file1);
    return EXIT_SUCCESS;
}
