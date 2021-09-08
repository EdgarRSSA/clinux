#include "../../prepare.h"

int main(int argc, char *argv[])
{
    // Check arguments:
    if (argc < 2)
    {
        printf("[%ld] Not file specified.\n", getpid());
        return EXIT_FAILURE;
    }
    // Save File path:
    const char *file_path = argv[1];

    // Open file:
    int file = open(file_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (file == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[%ld] Open: %s [%d]\n", getpid(), file_path, file);

    // CHECK FLAGS
    //
    //  int[binary]        FD     GET
    //                           FLAGS
    int file_flag = fcntl(file, F_GETFL);
    if ( file_flag == -1)
    {
        printf("[%ld] FCNTL Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }

    // CHECK O_SYNC
    if (file_flag & O_SYNC)
    {
        printf("[%ld] Writes are syncronized: O_SYNC[%d] [%d]\n", getpid(), file_flag, file);
    }
    // CHECK O_RDONLY
    if ( (file_flag & O_ACCMODE) == O_RDONLY)
    {
        printf("[%ld] File is Read only: O_RDONLY[%d] [%d]\n", getpid(), file_flag, file);
    }
    // CHECK O_WRONLY
    if ( (file_flag & O_ACCMODE) == O_WRONLY)
    {
        printf("[%ld] File is Write only: O_WRONLY[%d] [%d]\n", getpid(), file_flag, file);
    }
    // CHECK O_RDWR
    if ( (file_flag & O_ACCMODE) == O_RDWR)
    {
        printf("[%ld] File is Read and Write: O_RDWR[%d] [%d]\n", getpid(), file_flag, file);
    }


    // SET NEW FLAG TO FLAGS
    file_flag |= O_APPEND;
    if ( fcntl(file, F_SETFL, file_flag) == -1)
    {
        printf("[%ld] FCNTL F_SETFL Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[%ld] FCNTL F_SETFL.\n", getpid());

    // GET AND CHECK O_APPEND
    if ( fcntl(file, F_GETFL) & O_APPEND )
    {
        printf("[%ld] File is prepare to append: O_APPEND[%d] [%d]\n", getpid(), file_flag, file);
    }


    // Close file:
    if ( close(file) == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[%ld] Close: %s [%d]\n", getpid(), file_path, file);

    return EXIT_SUCCESS;
}
