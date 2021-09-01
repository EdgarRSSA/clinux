#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// MY DEFS
#define READ_BUFF_BYTES 1024 // 1KB

int main(int argc, char const *argv[])
{
    // OPEN
    char *file1_path = "./text.txt";
    int file1 = open(file1_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (file1 == -1) // Errors
    {
        printf("Open file: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Open file: %s\n", file1_path);

    // READ
    char *file1_buffer[READ_BUFF_BYTES + 1];
    file1_buffer[READ_BUFF_BYTES] = '\0';
    int file1_read = read(file1, file1_buffer, READ_BUFF_BYTES);
    if (file1_read == -1) // Errors
    {
        printf("Read file: %s\n",strerror(errno));
        close(file1);
        exit(EXIT_FAILURE);
    }

    printf("Content:%d\n\t%s\n", file1_read,file1_buffer);
    close(file1);
    return EXIT_SUCCESS;
}
