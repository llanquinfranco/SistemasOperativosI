#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para ftruncate(), read(), close()
#include <stdlib.h>

#define CABECERA 15
#define PIXELES 270000

int main(){
    const char *segmento = "Compartido";
    const char *nuevo = "archivo.ppm";
	int SIZE = CABECERA + PIXELES;
	unsigned char fusionada[SIZE];


    //const char *nombreArchivo;
    //scanf(nombreArchivo);


    // Abrir el segmento de memoria compartida
    int shm_fd = shm_open(segmento, O_RDONLY, 0666);
    if(shm_fd == -1) {
        printf("Error al abrir el segmento de memoria compartida\n");
        exit(-1);
    }

    // Mapear el segmento de memoria compartida en el espacio de direccion del proceso
    void *puntero = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if(puntero == MAP_FAILED) {
        printf("Mapeo fallido\n");
        exit(-1);
    }


    int f = open(nuevo, O_RDWR | O_CREAT | O_TRUNC, 0666);
    write(f, puntero, SIZE);
    close(f);


    // Eliminar el segmento de memoria compartida
    if(shm_unlink(segmento) == -1) {
        printf("Error al remover el segmento %s\n", segmento);
        exit(-1);
    }

    return 0;
}


