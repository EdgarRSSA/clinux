#include "../../prepare.h"

/**
 *  WRITE IN DIFERENT OFFSET BUFFERS IN A SINGLE FILE
 *  file in bytes :
 *  [0-19][20-39][40-59]...[20n-(20n+19)]
 *
*/

int main(int argc, char *argv[])
{
    // Check file arg:
    if( argc < 2){
        printf("[%ld] Error: Not file specified.\n",getpid());
        return EXIT_FAILURE;
    }
    if( argc < 3){
        printf("[%ld] Error: Not label specified.\n",getpid());
        return EXIT_FAILURE;
    }
    if( argc < 4){
        printf("[%ld] Error: Not offset specified.\n",getpid());
        return EXIT_FAILURE;
    }

    // Args
    char *file_path = argv[1]; // PATH FILE
    char *file_buffer[20]; // BUFFER SIZE
    char *arglabel = argv[2]; // LABEL TO WRITE IN BUFFER
    strcat(file_buffer, arglabel); // WRITE LABEL TO BUFFER
    strcat(file_buffer, "\0"); // WRITE NULL CHAR TO BUFFER
    int file_block = atoi(argv[3]); // FILE BLOCK
    int file_offset = file_block*20; // SPECIFIED THE BUFFER LOCATION-OFFSET TO WRITE IN FILE

    printf("[%ld] OFFSET[%d:%d] FILE[%s]\n", getpid(), file_block, file_offset, file_path);

#pragma region openfile // Open File
    int file = open(file_path, O_CREAT | O_RDWR  , S_IRUSR | S_IWUSR);
    if (file == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Open: %s[%d]\n", getpid(), file_path, file);
    }
#pragma endregion openfile



    // pwrite
    int file_pwrite = pwrite(file, file_buffer, strlen(file_buffer), file_offset);
    if ( file_pwrite == -1)
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] pwrite(...) TO %s[%d] OFFSET[%d:%d]: %d BYTES \n", getpid(), file_path, file, file_block, file_offset, file_pwrite);
    }

#pragma region closefile // Close FD
    if ( close(file) == -1 )
    {
        printf("[%ld] Error: %s\n", getpid(), strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Close: %s[%d]\n", getpid(), file_path, file);
    }
#pragma endregion closefile



    return EXIT_SUCCESS;
}
