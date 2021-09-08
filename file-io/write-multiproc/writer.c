#include <sys/fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    pid_t _PID = getpid();
    if (argc < 2)
    {
        printf("[%ld] Not file passed!\n",_PID);
        return EXIT_FAILURE;
    }else if (argc < 3)
    {
        printf("[%ld] Not label to write passed!\n",_PID);
        return EXIT_FAILURE;
    }

    // Save path
    const char *file_path = argv[1];

    // Save text to write
    const char *file_text = argv[2];

    // Open call:
    //
    // Add O_APPEND to ensure than lseek and write calls run atomically.
    //                 FILE      R/W    CREATE    APPEND    USERREAD   USERWRITE
    int file = open(file_path, O_RDWR | O_CREAT | O_APPEND , S_IWUSR | S_IRUSR);

    // Error in open call:
    if(file == -1){
        printf("[%ld] Error to open file: %s\n", _PID, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("[%ld] Open File %s : %d\n", _PID, file_path, file);

    // SEEK
    if (lseek(file,0,SEEK_END) == -1)
    {
        printf("[%ld] Error to seek in file: %s\n", _PID, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[%ld] Seek File.\n", _PID);


    // BUFFER
    char *buffer[1000];
    strcat(buffer, file_text);
    strcat(buffer, "\n");

    //  WRITE IN FILE
    if (write(file,buffer,strlen(buffer)) == -1)
    {
        printf("[%ld] Error to write in file: %s\n", _PID, strerror(errno));
        return EXIT_FAILURE;
    }


    printf("[%ld] Write text: %s\n", _PID, file_text);

    // Close call:
    if (close(file) == -1){
        printf("[%ld] Error to close: %s\n", _PID, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[%ld] Close.\n", _PID, file_path);

    return EXIT_SUCCESS;
}
