#include "./../../prepare.h"

int main(int argc, char *argv[])
{
    pid_t PID = getpid();

    printf("[%ld] Create a temporal file using mkstemp(...)\n", PID);

    // NAME
    char file_path[] = "./file.example.XXXXXX";
    printf("[%ld] Create file: %s\n", PID, file_path);

    // CREATE
    int file = mkstemp(file_path);

    if (file == -1)
    {
        printf("[%ld] mkstemp(...) Error: %s \n", PID, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("[%ld] File: %s[%d]\n", PID, file_path, file);

    sleep(3);

    // CLOSE
    unlink(file_path);
    if (close(file) == -1)
    {
        printf("[%ld] close(...) Error: %s \n", PID, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("[%ld] Close: %s[%d]\n", PID, file_path, file);

    return EXIT_SUCCESS;
}
