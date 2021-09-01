#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int socket_fd; // Socket File-Descriptor
const char *s_path = "./thesocket"; // Socket path

void handle_sigint(int sig) // MANEJADOR DE SEÑAL DE INTERRUPCION
{
    printf("close() : ok \n", sig);

    // Close
    close(socket_fd);

    // Exit
    exit(EXIT_FAILURE);
}




int main(){ // MAIN ENTRY

    // Crear un socket usando una llamada a la API
    // syscall -> socket()
    pid_t s_pid = getpid();
    printf("Socket PID:%d\n",s_pid);

    int s_domain = AF_UNIX; // ADDRESS FAMILY DOMAIN
    int s_type = SOCK_STREAM; // SOCKET STREAM TYPE
    int s_proto = PF_UNIX; // Local proto

    struct sockaddr s_address; // Socket Address
    s_address.sa_family = s_domain; // Socket domain for address
    strcpy(s_address.sa_data, s_path); // Copy path to sockaddr struct

    // Build socket
    socket_fd = socket(s_domain, s_type, s_proto);

    if (socket_fd == -1)
    {
        // Error al llamar socket():
        printf("socket(...) ERROR: %s\n",strerror(errno));

    }
    else
    {
        // Llamada a socket() correcta:
        printf("socket(...) FD: %d\n",socket_fd);

        // Verificar dirrecion del socket:
        struct stat sock_stat;
        stat(s_path, &sock_stat);
        printf("Address is Socket: %d\n",S_ISSOCK(sock_stat.st_mode));

        // Llamada a bind():
        if ( connect(socket_fd,&s_address,sizeof(s_address)) == -1)
        {
            // Error al llamar bind():
            printf("connect(...) ERROR: %s\n",strerror(errno));

        }
        else
        {
            // Llamada a bind() correcta:
            printf("connect(...) Address : %s\n",s_address.sa_data);

            char *buf="HELLO WORLD";
            if (write(socket_fd, buf, strlen(buf)) != strlen(buf)){
                printf("write(...)  Partial/failed");
            }
            printf("BUFFER : %s", buf);
            for (;;)
            {
                /* code */
            }
        }
    }

    return 0;
}
