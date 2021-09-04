#include <sys/fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * Ejecucion de 5 procesos que implementan de forma incorrecta la orden de
 * abrir un mismo archivo, Cada archivo abre el mismo, NO EXISTE EXCLUSIVIDAD
 *
 * [04:59:56] MAIN:./bad-exc-open.c RUN:./out/run FILE:./alfa.example.txt
 * [04:59:56] rm ./alfa.example.txt
 * [04:59:56] gcc -o ./out/run ./bad-exc-open.c
 * [04:59:56] ./out/run ./alfa.example.txt (5)
 * PID: 16305 PATHFILE: ./alfa.example.txt
 * PID: 16305 OPENERROR: No such file or directory
 * PID: 16305 REOPEN: ./alfa.example.txt
 * PID: 16307 PATHFILE: ./alfa.example.txt
 * PID: 16307 OPEN: ./alfa.example.txt FD: 3
 * PID: 16307 CLOSE: ./alfa.example.txt
 * PID: 16305 BADREOPEN: ./alfa.example.txt FD: 3
 * PID: 16305 CLOSE: ./alfa.example.txt
 * PID: 16306 PATHFILE: ./alfa.example.txt
 * PID: 16306 OPEN: ./alfa.example.txt FD: 3
 * PID: 16306 CLOSE: ./alfa.example.txt
 * PID: 16308 PATHFILE: ./alfa.example.txt
 * PID: 16308 OPEN: ./alfa.example.txt FD: 3
 * PID: 16308 CLOSE: ./alfa.example.txt
 * PID: 16309 PATHFILE: ./alfa.example.txt
 * PID: 16309 OPEN: ./alfa.example.txt FD: 3
 * PID: 16309 CLOSE: ./alfa.example.txt
*/


int main(int argc, char *argv[])
{
    // Revisar que se especifique un archivo a abrir:
    if(argc != 2){
        exit(EXIT_FAILURE);
    };
    char *exc_file_path = argv[1];
    printf("PID: %ld PATHFILE: %s\n", getpid(), exc_file_path);

    // Forma incorrecta de abrir un archivo de forma exclusiva:
    int exc_file_open = open(exc_file_path, O_WRONLY);
    if (exc_file_open == -1)
    {
        printf("PID: %ld OPENERROR: %s\n", getpid(),strerror(errno));

        // REINTENTO:

        printf("PID: %ld REOPEN: %s\n", getpid(), exc_file_path);
        exc_file_open = open(exc_file_path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if (exc_file_open == -1)
        {
            // Error al reintentar abrir archivo:
            printf("PID: %ld REOPENERROR: %s\n", getpid(),strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
        {
            // Se crea el archivo y se abre:
            printf("PID: %ld BADREOPEN: %s FD: %d\n", getpid(), exc_file_path, exc_file_open);
            close(exc_file_open);
            printf("PID: %ld CLOSE: %s\n", getpid(),exc_file_path);
        }

    }
    else
    {
        // Archivo abierto:
        printf("PID: %ld OPEN: %s FD: %d\n", getpid(), exc_file_path, exc_file_open);
        close(exc_file_open);
        printf("PID: %ld CLOSE: %s\n", getpid(),exc_file_path);
    }

    return EXIT_SUCCESS;
}
