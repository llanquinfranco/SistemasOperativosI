#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para ftruncate(), read(), close()
#include <stdlib.h>

#define SIZE 50261
#define CABECERA 15

/* Un segundo programa lee de la memoria compartida la foto, y la guarda en un nuevo
archivo de manera invertida. */
int main() {
    const char *nombre = "Compartido";
    const char *nuevo = "cat2.pgm";

    int shm_fd = shm_open("Compartido", O_RDONLY, 0666);
    if(shm_fd == -1) {
        printf("Error al abrir el segmento de memoria compartida (Programa 2)\n");
        exit(-1);
    }

    // Para probar c.
    sleep(8);

    // Mapear el segmento de memoria compartida en el espacio de direccion del proceso
    void *puntero = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 
    if(puntero == MAP_FAILED) {
        printf("Mapeo fallido (Programa 2)\n");
        exit(-1);
    }

    sleep(8);

    // b. Agregue sentencias para emitir la dirección virtual del inicio del segmento de memoria compartida 
    printf("Dirección virtual del segmento compartido: %p\n", puntero);

    int fd = open(nuevo, O_RDWR | O_CREAT | O_TRUNC, 0666);     // Le pide al sistema operativo crear un archivo nuevo 
    if (fd == -1) {
        printf("Error al crear el archivo cat2.pgm (Programa 2)\n");
        exit(-1);
    }
    
    unsigned char *imagen = (unsigned char *) puntero;

    // Escribo en el archivo nuevo, la cabecera intacta
    for(int i = 0; i < CABECERA; i++) {
        write(fd, &imagen[i], 1);
    }
    // Escribo en el archivo nuevo, los pixeles invertidos
    for(int j = SIZE - 1; j >= CABECERA; j--) {
        write(fd, &imagen[j], 1);
    }

    // Cerrar el archivo nuevo
    if(close(fd) == -1) {
        printf("Error al cerrar el archivo (Programa 2)\n");
    }

    // Eliminar el segmento de memoria compartida
    if(shm_unlink(nombre) == -1) {
        printf("Error al remover el segmento de memoria compartida (Programa 2)\n");
        exit(-1);
    }

    return 0;
}