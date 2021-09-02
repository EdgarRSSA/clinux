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
    int file1 = open(file1_path, O_RDONLY);
    if (file1 == -1) // Errors
    {
        printf("Open file: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Open file: %s\n", file1_path);

    // READ
    u_int16_t file1_buffer[(int)(READ_BUFF_BYTES / 2)];
    int file1_read = read(file1, file1_buffer, READ_BUFF_BYTES);
    if (file1_read == -1) // Errors
    {
        printf("Read file: %s\n",strerror(errno));
        close(file1);
        exit(EXIT_FAILURE);
    }
    printf("Content Read: %d\n", file1_read);
    char *sep = ":";
    for (size_t i = 0; i < (int)(READ_BUFF_BYTES / 2); i++)
    {
        // 160 * 2B = 320B
        if (((i+1)%32) == 0)
        {
            printf("%X\n", (u_int16_t)file1_buffer[i], sep);
        }
        else
        {
            printf("%X%s", (u_int16_t)file1_buffer[i], sep);
        }
    }
    printf("\n");

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
