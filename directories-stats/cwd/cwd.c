#pragma region INCLUDES
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
    Definitions:
*/
#define APP_ERROR -1
#define APP_SUCCESS 0
#define APP_WARNNING 1

#pragma endregion

#include <dirent.h>

/**
 * Read the Directory content.
 * @param pathname Directory Path.
 * @return APP_DEFINED Code.
*/
int read_dir_content(char *pathname){

    // OPEN DIR
    DIR *__sdir = opendir(pathname);
    if (__sdir == NULL)
    {
        printf("opendir(%s) Error.\n",pathname);
        return APP_ERROR;
    }

    // READ AND PRINT CONTENTS USING FORLOOP
    struct dirent *__sdir_entrie;
    int __sdir_entrie_error = 0;
    int __sdir_counter = 0;
    for (;;)
    {
        __sdir_counter += 1;
        __sdir_entrie = readdir(__sdir);
        if (__sdir_entrie == NULL)
        {
            __sdir_entrie_error = errno;
            break;
        }
        char __sdirpath[254] = "";
        sprintf(__sdirpath, "%s/%s", pathname, __sdir_entrie->d_name);

        printf("\t%s\n", __sdir_entrie->d_name);
    }

    //  CHECK ERROR OR END OF LOOP CODE
    if (__sdir_entrie_error != 0)
    {
        printf("readdir(...) <%s> Error: %s\n", pathname,strerror(__sdir_entrie_error));
        if (closedir(__sdir) == -1)
        {
            printf("closedir(...)<%s> Error.\n", pathname);
            return APP_ERROR;
        }
        return APP_ERROR;
    }

    // CLOSE DIR
    if (closedir(__sdir) == -1)
    {
        printf("closedir(...)<%s> Error.\n", pathname);
        return APP_ERROR;
    }
    // SUCCESS END
    return APP_SUCCESS;
}



int main(int argc, char const *argv[])
{

    // CHECK ENV: CWD_DIR
    char const *CWD_DIR;
    CWD_DIR = getenv("CWD_DIR");
    if (CWD_DIR != NULL)
    {
        // CHANGE CWD
        printf("Change CWD using CWD_DIR:%s\n", CWD_DIR);
        if(chdir(CWD_DIR)==-1){
            printf("chdir(CWD_DIR) Error:%s", strerror(errno));
            return EXIT_FAILURE;
        }
    }

    // GET CWD
    size_t cwd_buff = 100;
    char cwd[cwd_buff];
    if (getcwd(cwd, cwd_buff) == NULL){
        printf("getcwd(%xh,%d) Error: %s\n", cwd, cwd_buff, strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Process Current Working Directory:%s\n",cwd);


    // Read directory content:
    read_dir_content(cwd);

    return EXIT_SUCCESS;
}
