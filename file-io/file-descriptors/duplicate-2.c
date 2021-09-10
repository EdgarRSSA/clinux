#include "../../prepare.h"

int main(int argc, char *argv[])
{
    // Check file arg:
    if( argc != 2){
        printf("[%ld] Error: Not file specified.\n",getpid());
        return EXIT_FAILURE;
    }
    // File path:
    char *file_path = argv[1];
    printf("[%ld] File path: %s\n", getpid(), file_path);

    // open
    int file = open(file_path, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (file == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Open: %s[%d]\n", getpid(), file_path, file);
    }

    // Duplicate using predefined FD
    int file2 = dup2(file,10);
    if (file2 == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Duplicate using [10] FD: %s[%d]\n", getpid(), file_path, file2);
    }

    // Close 1FD
    if ( close(file) == -1 )
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Close: %s[%d]\n", getpid(), file_path, file);
    }

    // lseek usinf 2FD
    if (lseek(file2,0,SEEK_END ) == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Seek to end 0 in [%d] \n", getpid(), file2);
    }

    // Write usinf 2FD
    char *buff = "ALFA123\n";
    if (write(file2,buff,strlen(buff) ) == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Write in [%d]: %d bytes \n", getpid(), file2, strlen(buff));
    }

    // Close 2FD
    if ( close(file2) == -1 )
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Close: %s[%d]\n", getpid(), file_path, file2);
    }

    return EXIT_SUCCESS;
}
