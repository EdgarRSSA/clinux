#include "./read-dir.h"


/**
 * Read the Directory content.
 * @param pathname Directory Path.
 * @return APP_DEFINED Code.
*/
int read_dir_content(char *pathname){

#ifdef DEBUG
    printf("<directory> %s\n", pathname);
#endif

    // OPEN DIR
    DIR *__sdir = opendir(pathname);
    if (__sdir == NULL)
    {
        printf("opendir(%s) Error.\n",pathname);
        return APP_ERROR;
    }

#ifdef DEBUG
    printf("<opendir> %s [%ld]\n", pathname, dirfd(__sdir));
#endif

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
#ifdef DEBUG
        printf("<readdir> [%d]\n", __sdir_counter);
#endif
        char __sdirpath[254] = "";
        sprintf(__sdirpath, "%s/%s", pathname, __sdir_entrie->d_name);

        printf("\tTYPE:%d NAME:%s INODE:%d PATH:%s\n", __sdir_entrie->d_type, __sdir_entrie->d_name, __sdir_entrie->d_ino, __sdirpath);
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

#ifdef DEBUG
    printf("<closedir> %s\n", pathname);
#endif

    // SUCCESS END
    return APP_SUCCESS;
}
