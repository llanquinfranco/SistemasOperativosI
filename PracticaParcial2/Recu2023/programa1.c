#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para ftruncate(), read(), close()

// El tamaño de la memoria compartida es estático y conocido: 50261 bytes
#define SIZE 50261

/* Un programa crea memoria compartida, y carga en la memoria compartida la foto cat.pgm, 
usando funciones para acceder a archivos en el sistema de archivos.*/
int main() {
    const char *nombre = "Compartido";
    const char *ruta = "cat.pgm";

    int file_fd;
    void *puntero;

    // Crear el segmento de memoria compartida
    int shm_fd = shm_open(nombre, O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1) {
        printf("Error al crear el segmento de memoria compartida (Programa 1)\n");
        return -1;
    }

    // Configurar el tamaño del segmento de memoria compartida
    if (ftruncate(shm_fd, SIZE) == -1) {
        printf("Error al establecer tamaño de memoria compartida (Programa 1)\n");
        return -1;
    }

    // Mapear el segmento de memoria compartida en el espacio de direccion del proceso
    puntero = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(puntero == MAP_FAILED) {
        printf("Mapeo fallido (Programa 1)\n");
        return -1;
    }

    // Abrir el archivo solo para lectura
    file_fd = open(ruta, O_RDONLY);
    if (file_fd == -1) {
        printf("Error al abrir el archivo (Programa 1)\n");
        return -1;
    }

    // Leer el contenido del archivo y copiarlo a la memoria compartida
    ssize_t bytesLeidos = read(file_fd, puntero, SIZE);
    if (bytesLeidos == -1) {
        printf("Error al leer el archivo (Programa 1)\n");
        return -1;
    }

    // Cerrar el archivo
    if(close(file_fd) == -1) {
        printf("Error al cerrar el archivo (Programa 1)\n");
    }

    return 0;
}




