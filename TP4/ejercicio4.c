#include <stdio.h>
#include <stdlib.h>     // malloc(), exit()
#include <fcntl.h>      // open(), constantes O_
#include <unistd.h>     // read(), close()

int file_get_size(const char nombre_de_archivo[]) {
    const int SIZE = 1024; // Tamaño de lectura por bloque
    char buffer[SIZE];
    int tamanio = 0;
    int leido;

    // Abrir el archivo solo para lectura
    int fd = open(nombre_de_archivo, O_RDONLY);
    if (fd == -1) {
        printf("Error al abrir el archivo\n");
        exit(-1);
    }

    // Contar por bloques
    while ((leido = read(fd, buffer, SIZE)) > 0) {
        if (leido == -1) {
            printf("Error al leer el archivo\n");
            close(fd);
            exit(-1);
        }
        tamanio = tamanio + leido;
    }

    close(fd);
    return tamanio;
}

int main() {
    // Uso otra ruta ya que mi linux no tiene el archivo /usr/share/doc/libsdl1.2-dev/docs.html
    const char *nombreArchivo = "/etc/hostname";
    int tamanioArchivo = file_get_size(nombreArchivo);

    // Reabrir archivo para leer su contenido
    int fd = open(nombreArchivo, O_RDONLY);
    if (fd == -1) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    // Reservar espacio dinamicamente
    char *puntero = malloc(tamanioArchivo);
    if (puntero == NULL) {
        close(fd);
        printf("Error al reservar memoria dinamicamente\n");
        return -1;
    }
    
    // Leer todo el contenido y guardarlo en memoria ¿?
    int estado = read(fd, puntero, tamanioArchivo);
    if(estado < 0) {
        free(puntero);
        close(fd);
        printf("Error al leer el archivo\n");
        return -1;
    }

    // Imprimir en orden inverso
    for(int i = tamanioArchivo - 1; i >= 0; i--) {
        printf("%c", puntero[i]);
    }
    printf("\n");

    free(puntero);
    close(fd);

    return 0;
}

/*
// Imprimir en orden inverso (sin salto de linea apenas empieza)

for(int i = tamanioArchivo - 1; i >= 0; i--) {
    if(puntero[i] != '\n') {
        printf("%c", puntero[i]);
    }
}
printf("\n");

o

int start = tamanioArchivo - 1;
if (puntero[start] == '\n') {
    start--;
}
for(int i = start; i >= 0; i--) {
    printf("%c", puntero[i]);
}
*/