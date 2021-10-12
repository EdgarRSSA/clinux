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
    // Args
    //
    printf("Info about Process Arguments 'argc' : %d\n", argc);
    printf("Info about Process Arguments : \n");
    for (int i = 0; i < argc; i++)
    {
        printf("\targv[%d] : %s\n", i, argv[i]);
    }


    //
    // Env from global 'environ'
    //
    printf("Info about Process Environment: 'extern char **environ' \n");
    for (char **env_i = environ; *env_i != NULL; env_i++)
    {
    //          ^         ^           ^           ^
    //          |         |           |           |
    //      pointer    list-env     Is NULL?  pointer++

        printf("\tenviron[%Xh] : %s\n", env_i, *env_i);

    }


    //
    // Env from main(...)
    //
    printf("Info about Process Environment: 'main(... , char *envp[])' \n");
    for (char **env_i = envp; *env_i != NULL; env_i++)
    {
    //          ^         ^           ^           ^
    //          |         |           |           |
    //      pointer    list-env     Is NULL?  pointer++

        printf("\tenvp[%Xh] : %s\n", env_i, *env_i);

    }


    //
    // Get SHELL Env:
    //
    char *shell_env = "SHELL";
    char *shell_val = getenv(shell_env);
    printf("Process Env -> %s : %s \n", shell_env, shell_val);


    //
    // SET Env:
    //
    char *CL_env = "CLINUX_X";
    char *CL_val = "XXXX";
    if ( setenv(CL_env,CL_val,1) == -1)
    {
        printf("PUT Process Env  Error : %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    else
    {
        printf("SET Process Env -> %s : %s \n", CL_env, CL_val);
    }


    //
    // CLEAR AND PUT Env:
    //

    // Clear env.
    if ( clearenv() != 0 )
    {
        printf("CLEAR Process Env Error : %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("Clear Process Environment. \n");

    // Put env.
    char *CL2_env = "CLINUX_Y=YYYY";
    if ( putenv(CL2_env) != 0 )
    {
        printf("PUT Process Env  Error : %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    printf("PUT Process Env -> %s \n", CL2_env);

    // Print env:
    printf("List Process Env : \n");
    for (char **env_i = environ; *env_i != NULL; env_i++)
    {
        printf("\tenviron[%Xh] : %s\n", env_i, *env_i);
    }


    return EXIT_SUCCESS;
}
