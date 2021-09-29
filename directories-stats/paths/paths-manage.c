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

#include <libgen.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    char *rp;
    char *bn;
    char *dn;
    struct stat *rp_stat;

    for (size_t i = 0; i < argc; i++)
    {
        rp = realpath(argv[i], NULL);
        bn = basename(rp);
        dn = dirname(rp);

        printf("\t%s \n\tdirname %s \n\tbasename %s \n\n", rp, dn, bn);
    }

    return 0;
}
