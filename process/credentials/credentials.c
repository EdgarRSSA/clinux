#include "./../../prepare.h"

extern char **environ;

int main(int argc, char const *argv[],char const *envp[])
{
    //
    // PIDs
    //
    pid_t PPID = getppid();
    pid_t PID = getpid();
    printf("Info about Parent Process ID: %ld\n", PPID);
    printf("Info about Process ID: %ld\n", PID);

    //
    // Real User ID y Real Group ID
    //
    uid_t user_id = getuid();
    uid_t group_id = getgid();
    printf("Real User ID: %ld\n", user_id);
    printf("Real Group ID: %ld\n", group_id);

    //
    // Efective User ID y Efective Group ID
    //
    uid_t efective_user_id = geteuid();
    uid_t efective_group_id = getegid();
    printf("Efective User ID: %ld\n", efective_user_id);
    printf("Efective Group ID: %ld\n", efective_group_id);

    return EXIT_SUCCESS;
}
