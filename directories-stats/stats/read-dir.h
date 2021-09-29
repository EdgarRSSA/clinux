#ifndef APP_DEF
#define APP_DEF
/*
    Normal Libs:
*/
#include <sys/fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
    Exclusive work libs:
*/
#include <dirent.h>


/*
    Definitions:
*/
#define APP_ERROR -1
#define APP_SUCCESS 0
#define APP_WARNNING 1


/*
    Headers:
*/

int main(int argc, char *argv[]);
int read_dir_content(char *pathname);

#endif
