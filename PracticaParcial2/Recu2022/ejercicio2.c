#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char *argv[]) {


    if (argc < 3) {
        printf("error: al menos ejecutar con 2 argumentos\n");
        exit(1);
    }
    printf("argumento1: %s   argumento2: %s \n", argv[1], argv[2]);

    /* etc */

    // abrir aqui el archivo argv[1] como solo lectura
    int f1 = open(argv[1], O_RDONLY);
    if(f1 == -1) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    // creamos el nuevo archivo
    int f2 = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
    if(f2 == -1) {
        printf("Error al crear el archivo\n");
        exit(1);
    }

    // copie cada byte del archivo f1 en f2, al llegar al final, cerrar los dos archivos
    int estado;
    char caracter;

    while(1) {
        estado = read(f1, &caracter, 1);    // Lee un byte del archivo original
        if(estado == -1) {                  // Si hubo un error
            printf("Error al copiar los bytes\n");
            close(f1);
            close(f2);
            exit(1);
        } else if(estado == 0) {            // Si llego al final (EOF - End of file)
            printf("Llego al final\n");
            close(f1);
            close(f2);
            break;
        } else {                            // Escribo ese byte en el archivo copia
            write(f2, &caracter, 1);
        }
    }
}