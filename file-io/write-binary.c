#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// MY DEFS
#define READ_BUFF_BYTES 320 // 160*2B = 320B
#define WRITE_BUFF_BYTES 320 // 160*2B = 320B

int main(int argc, char const *argv[])
{
    // OPEN Binary file
    char *file1_path = "./numbers.ed";
    int file1 = open(file1_path, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (file1 == -1) // Errors
    {
        printf("Open file: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Open file: %s\n", file1_path);

    // WRITE BINARY DATA
    u_int16_t file1_wbuffer[(int)(WRITE_BUFF_BYTES / 2)];
    for (size_t i = 0; i < ((int)(WRITE_BUFF_BYTES / 2)); i++)
    {
        // 160 * 2B = 320B
        file1_wbuffer[i] = (u_int16_t)i+100;
    }
    //file1_wbuffer[(int)(WRITE_BUFF_BYTES / 2)] = (u_int16_t)0xFF02;

    int file1_write = write(file1, file1_wbuffer,WRITE_BUFF_BYTES);

    if (file1_write == -1) // Errors
    {
        printf("Write file: %s\n",strerror(errno));
        close(file1);
        exit(EXIT_FAILURE);
    }
    printf("Content Write: %d\n", file1_write);

    // Close
    int file1_close = close(file1);
    if (file1_close == -1) // Errors
    {
        printf("Close file: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Close file: %s\n", file1_path);
    return EXIT_SUCCESS;
}
