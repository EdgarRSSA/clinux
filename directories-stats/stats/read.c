#include "./read-dir.h"

/**
 * Main Entry-point.
 * @param argc arguments counter.
 * @param argv arguments string array.
 * @return Exit process code.
 * */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Arguments incorrect.\n");
        return EXIT_FAILURE;
    }

    printf("Read DIR:%s\n", argv[1]);

    if (read_dir_content(argv[1]) == APP_ERROR){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
