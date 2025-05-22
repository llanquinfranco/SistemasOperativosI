#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para ftruncate(), read(), close()
#include <stdlib.h>

int main() {
    const int SIZE = 4096;
    const char *name = "Compartido";

    int shm_fd, i;
    void *ptr;

    // Abrir el segmento de memoria compartida
    shm_fd = shm_open("Compartido", O_RDONLY, 0666);
    if(shm_fd == -1) {
        printf("Error al abrir el segmento de memoria compartida\n");
        exit(-1);
    }

    // Mapear el segmento de memoria compartida en el espacio de direccion del proceso
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED) {
        printf("Mapeo fallido\n");
        exit(-1);
    }

    // Leer y mostrar desde el segmento de memoria compartida
    printf("Contenido de la memoria compartida: %s", (char *)ptr);

    // Eliminar el segmento de memoria compartida
    if(shm_unlink(name) == -1) {
        printf("Error al remover el segmento %s\n", name);
        exit(-1);
    }

    return 0;
}