#include "./../../prepare.h"

int main(int argc, char *argv[])
{
    pid_t PID = getpid();

    printf("[%ld] Create a temporal file using tmpfile(...)\n", PID);

    // CREATE
    FILE *file = tmpfile();

    if (file == NULL)
    {
        printf("[%ld] tmpfile(...) Error: %s \n", PID, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("[%ld] File: tmpfile[0x%x]\n", PID, file);

    sleep(3);

    printf("[%ld] Close: tmpfile[0x%x]\n", PID, file);

    return EXIT_SUCCESS;
}
