#include "../../prepare.h"

/**
 *  READ FROM DIFERENT OFFSET BUFFERS IN A SINGLE FILE
 *  file in bytes :
 *
 *  [0-19] [20-39] [40-59] ... [20n-(20n+19)]
 *
 *    0       1       2    ...     n
 *
*/

int main(int argc, char *argv[])
{
    // PID
    pid_t PROGPID = getpid();
    // Check file arg:
    if( argc < 2){
        printf("[%ld] Error: Not file specified.\n",PROGPID);
        return EXIT_FAILURE;
    }
    if( argc < 3){
        printf("[%ld] Error: Not offset specified.\n",PROGPID);
        return EXIT_FAILURE;
    }

    // Args
    char *file_path = argv[1]; // PATH FILE
    int file_buffer_size = 20;
    char *file_buffer[file_buffer_size];  // BUFFER
    int file_block = atoi(argv[2]); // FILE BLOCK
    int file_offset = file_block * 20; // SPECIFIED THE BUFFER LOCATION-OFFSET TO WRITE IN FILE

    printf("[%ld] OFFSET[%d:%d]\n", PROGPID, file_block, file_offset);

#pragma region openfile // Open File
    int file = open(file_path, O_CREAT | O_RDWR  , S_IRUSR | S_IWUSR);
    if (file == -1)
    {
        printf("[%ld] Error: %s\n", PROGPID, strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Open: %s[%d]\n", PROGPID, file_path, file);
    }
#pragma endregion openfile



    // pread
    int file_pread = pread(file, file_buffer, file_buffer_size, file_offset);
    if (file_pread == -1)
    {
        printf("[%ld] Error: %s\n", PROGPID, strerror(errno));
        return EXIT_FAILURE;
    }
    else if ( file_pread == 0 )
    {
        printf("[%ld] EOF: %s\n", PROGPID, file_path);
    }
    else
    {
        printf("[%ld] pread(...) FROM %s[%d] OFFSET[%d:%d] : %s[%d] \n", PROGPID, file_path, file, file_block, file_offset, file_buffer, file_pread);
    }

#pragma region closefile // Close FD
    if ( close(file) == -1 )
    {
        printf("[%ld] Error: %s\n", PROGPID, strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("[%ld] Close: %s[%d]\n", PROGPID, file_path, file);
    }
#pragma endregion closefile



    return EXIT_SUCCESS;
}
