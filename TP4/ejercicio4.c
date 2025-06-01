#include <stdio.h>
#include <stdlib.h>     // Para malloc(), exit()
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para open(), read(), close()


int file_get_size(const char nombreArchivo[]) {
    const int SIZE = 1024; // Tamaño de lectura por bloque
    int tamaño = 0;

    // Abrir el archivo solo para lectura
    int file_fd = open(nombreArchivo, O_RDONLY);
    if (file_fd == -1) {
        printf("Error al abrir el archivo\n");
        exit(-1);
    }

    char buffer[SIZE];
    int bytesLeidos;

    while((bytesLeidos = read(file_fd, buffer, SIZE)) > 0) {
        tamaño = tamaño + bytesLeidos;
    }

    close(file_fd);

    return tamaño;
}

int main() {
    // Uso otra ruta ya que mi linux no tiene el archivo /usr/share/doc/libsdl1.2-dev/docs.html
    const char *nombreArchivo = "/etc/hostname";    

    int cantBytes = file_get_size(nombreArchivo);

    // Reservar espacio dinamicamente
    char *contenido = malloc(cantBytes);
    if (contenido == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    // Reabrir archivo para leer su contenido
    int file_fd = open(nombreArchivo, O_RDONLY);
    if (file_fd == -1) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    // Leer todo el contenido
    int totalLeido = 0;
    int leido;
    while((leido = read(file_fd, contenido + totalLeido, cantBytes - totalLeido)) > 0) {
        totalLeido = totalLeido + leido;
    }
    close(file_fd);
    
    // Imprimir en orden inverso
    for(int i = cantBytes - 1; i >= 0; i--) {   // cantBytes - 2 para evitar salto de linea en terminal ¿?
        putchar(contenido[i]);
    }
    putchar('\n');      // Mejora salida por terminal
    free(contenido);    // Libera la memoria dinamica reservada anteriormente

    return 0;
}