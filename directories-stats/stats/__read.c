#include "./read-dir.h"

#define __USE_XOPEN_EXTENDED
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <time.h>

int info(   const char *__filename,
		    const struct stat *__status,
            int __flag,
		    struct FTW *__info){
    // STATS
    int BUF_SIZE = 100;

    char time_creat[BUF_SIZE];
    struct tm *tmc = localtime(&(__status->st_ctim));
    size_t stimec = strftime(time_creat, BUF_SIZE, "%x %X", tmc);

    char time_modif[BUF_SIZE];
    struct tm *tmm = localtime(&(__status->st_mtim));
    size_t stimem = strftime(time_modif, BUF_SIZE, "%x %X", tmm);

    char time_acces[BUF_SIZE];
    struct tm *tma = localtime(&(__status->st_atim));
    size_t stimea = strftime(time_acces, BUF_SIZE, "%x %X", tma);

    char *__type;
    switch (__status->st_mode & S_IFMT)
    {
    case S_IFREG:
        __type = "Regular File";
        break;
    case S_IFDIR:
        __type = "Directory";
        break;
    case S_IFCHR:
        __type = "Character Device";
        break;
    case S_IFBLK:
        __type = "Block Device";
        break;
    case S_IFIFO:
        __type = "FIFO/PIPE";
        break;
    case S_IFSOCK:
        __type = "Socket";
        break;
    case S_IFLNK:
        __type = "Symbolic Link";
        break;
    default:
        __type = "Unknown type";
        break;
    };

    printf("\t%s \n\ttype %s \n\t%ld UID %ld bytes %ld blocks %ld base %ld level \n\tStatus Change %s \n\tModification %s \n\tAccess %s\n\n",
                                    realpath(__filename,NULL),
                                    __type,
                                    __status->st_uid,
                                    __status->st_size,
                                    __status->st_blocks,
                                    __info->base,
                                    __info->level,
                                    time_creat,
                                    time_modif,
                                    time_acces);
    return 0; // CONTINUE NFTW
}

/**
 * Read the Directory content and show stats.
 * @param pathname Directory Path.
 * @return APP_DEFINED Code.
*/
int read_dir_content(char *pathname){

   // open and run
   int nftw_fds = 20;
   int nftw_flags = 0;
   int nftw_code = nftw(pathname, info, nftw_fds, nftw_flags);
   if (nftw_code == -1)
   {
       printf("nftw(%s,info<%x>,%d,%x) Error: %s\n", pathname, info, nftw_fds, nftw_flags, strerror(errno));
       return APP_ERROR;
   }

   // SUCCESS END
   return APP_SUCCESS;
}
