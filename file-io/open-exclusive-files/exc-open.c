#include <sys/fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Prueba de funcionamiento en 5 procesos diferentes que abren un archivo de forma exclusiva,
 * el primer proceso en ejecutar la orden open() de forma exclusiva es el unico que puede
 * trababajar en el.
 *
 * [05:05:25] MAIN:./exc-open.c RUN:./out/run FILE:./alfa.example.txt
 * [05:05:25] rm ./alfa.example.txt
 * [05:05:25] gcc -o ./out/run ./exc-open.c
 * [05:05:25] ./out/run ./alfa.example.txt (5)
 * PID: 17249 PATHFILE: ./alfa.example.txt
 * PID: 17249 OPEN: ./alfa.example.txt FD: 3
 * PID: 17249 CLOSE: ./alfa.example.txt
 * PID: 17253 PATHFILE: ./alfa.example.txt
 * PID: 17253 OPENERROR: File exists
 * PID: 17250 PATHFILE: ./alfa.example.txt
 * PID: 17250 OPENERROR: File exists
 * PID: 17252 PATHFILE: ./alfa.example.txt
 * PID: 17252 OPENERROR: File exists
 * PID: 17251 PATHFILE: ./alfa.example.txt
 * PID: 17251 OPENERROR: File exists
 *
*/

int main(int argc, char *argv[])
{
    // Revisar que se especifique un archivo a abrir:
    if(argc != 2){
        exit(EXIT_FAILURE);
    };
    char *exc_file_path = argv[1];
    printf("PID: %ld PATHFILE: %s\n", getpid(), exc_file_path);

    // Abrir archivo de forma exclusiva:
    int exc_file_open = open(exc_file_path, O_RDWR | O_EXCL | O_CREAT , S_IRUSR | S_IWUSR);
    if (exc_file_open == -1)
    {
        // Error al abrir
        printf("PID: %ld OPENERROR: %s\n", getpid(),strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        // Archivo abierto, Cerrar:
        printf("PID: %ld OPEN: %s FD: %d\n", getpid(), exc_file_path, exc_file_open);
        close(exc_file_open);
        printf("PID: %ld CLOSE: %s\n", getpid(),exc_file_path);
    }

    return EXIT_SUCCESS;
}
