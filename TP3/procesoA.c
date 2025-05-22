#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para ftruncate(), read(), close()

int main() {
    const int SIZE = 4096;
    const char *name = "Compartido";
    const char *path = "/etc/hostname"; // Puse otra ruta porque en mi PC no tengo el archivo 06mmap.txt

    int shm_fd, file_fd;
    void *ptr;

    // Crear el segmento de memoria compartida
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Configurar el tamaño del segmento de memoria compartida
    ftruncate(shm_fd, SIZE);

    // Mapear el segmento de memoria compartida en el espacio de direccion del proceso
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED) {
        printf("Mapeo fallido\n");
        return -1;
    }

    // Abrir el archivo solo para lectura
    file_fd = open(path, O_RDONLY);
    if (file_fd == -1) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    // Leer el contenido del archivo y copiarlo a la memoria compartida
    ssize_t bytes_read = read(file_fd, ptr, SIZE - 1);  // Dejar un byte para '\0'
    if (bytes_read == -1) {
        printf("Error al leer el archivo\n");
        return -1;
    }

    // Asegurar la terminacion de string
    ((char *)ptr)[bytes_read] = '\0';

    // Cerrar el archivo
    if(close(file_fd) == -1) {
        printf("Error al cerrar el archivo\n");
    }

    return 0;
}