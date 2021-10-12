#include "./../../prepare.h"

#include <sys/utsname.h>

void readprocfile(char proc_file[]){

    char proc_pid_file[40];
    pid_t PID = getpid();

    sprintf(proc_pid_file, "/proc/%d/%s", PID, proc_file);

    int fd = open(proc_pid_file, O_RDONLY);

    if (fd == -1){
        exit(EXIT_FAILURE);
    }

    size_t readlen = 2048;
    char readbuffer[readlen];
    if (read(fd, readbuffer, readlen) == -1)
    {
        printf("read(...) Error:%s\n", strerror(errno));
        if (close(fd) == -1)
        {
            printf("close(...) Error:%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }

    printf("\t%s : %s\n", proc_pid_file, readbuffer);

    if (close(fd) == -1)
    {
        printf("close(...) Error:%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[]){

    /**
     *  System Identification: uname()
     *  The uname() system call returns a range of identifying information about the
     *  host system on which an application is running, in the structure pointed to
     *  by utsbuf.
    */
    struct utsname utsbuf;
    int uname_status = uname(&utsbuf);
    if (uname_status)
    {
        printf("uname(...) Error:%s\n", strerror(errno));
    }
    printf("System Identification:\n");
    printf("\tOS Name:  %s\n", utsbuf.sysname);
    printf("\tNetwork Node:  %s\n", utsbuf.nodename);
    printf("\tNIS Domain:  %s\n", utsbuf.__domainname);
    printf("\tRealease:  %s\n", utsbuf.release);
    printf("\tVersion:  %s\n", utsbuf.version);
    printf("\tHardware Type:  %s\n", utsbuf.machine);

    /*
        Info from /proc/PID/
            cmdline      Command-line arguments delimited by \0
            cwd          Symbolic link to current working directory
            environ      Environment list NAME=value pairs, delimited by \0
            exe          Symbolic link to file being executed
            fd           Directory containing symbolic links to files opened by this process
            maps         Memory mappings
            mem          Process virtual memory (must lseek() to valid offset before I/O)
            mounts       Mount points for this process
            root         Symbolic link to root directory
            status       Various information (e.g., process IDs, credentials, memory usage, signals)
            task         Contains one subdirectory for each thread in process (Linux 2.6)
    */

    printf("\n/PROC/PID/<FILE>:\n");
    readprocfile("cmdline");
    readprocfile("environ");
    readprocfile("status");

    return EXIT_SUCCESS;
}
