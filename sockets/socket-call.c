#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>


int main(){

    // Crear un socket usando una llamada a la API
    // syscall -> socket()
    printf("SYSCALL: socket(DOMAIN,TYPE,PROTO)\n");

    int file_descriptor; // DESCRIBE EL SOCET CREADO
    int s_domain = AF_UNIX; // ADDRESS FAMILY DOMAIN
    int s_type = SOCK_STREAM; // SOCKET STREAM TYPE
    int s_proto = 0;

    file_descriptor = socket(s_domain, s_type, s_proto);

    if (file_descriptor == -1)
    {
        printf("ERROR::SYSCALL:socket(...) : %s\n",strerror(errno));
    } else
    {
        printf("FD::SYSCALL:socket(...) : %d\n",file_descriptor);
    }



}
