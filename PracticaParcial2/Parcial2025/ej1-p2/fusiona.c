#include "imagen1.h"
#include "imagen2.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define CABECERA 15
#define PIXELES 270000

int main() {
	const char *segmento = "Compartido";
	int SIZE = CABECERA + PIXELES;
	unsigned char fusionada[SIZE];

	// Guardar la cabecera
	for(int i = 0; i < CABECERA; i++){
		fusionada[i] = cabecera1[i];
	}

	int j = CABECERA;
	// Fusionar pixeles
	for(int i = 0; i < PIXELES; i++) {
		if(i % 2 == 0) {
			fusionada[j] = pixels2[i];
		} else {
			fusionada[j] = pixels1[i];
		}
		j++;
	}

	// en image1.h e imagen2.h están los arreglos de las imágenes
	// los arreglos son de tipo: unsigned char
	
	// cabecera1[] tiene 15 bytes que son la cabecera de la imagen
	
	// pixels1[4]  tiene el pixel 4 de la imagen 1
	// pixels1[5]  tiene el pixel 5 de la imagen 1
	
	// pixels2[10]  tiene el pixel 10 de la imagen 2

	// Crear segmento de memoria compartida
	int shm_fd = shm_open(segmento, O_CREAT | O_RDWR, 0666);

	// Configurar el tamaño de memoria compartida
	ftruncate(shm_fd, SIZE);

	// Mapear el segmento de memoria compartida en el espacio de direccion del proceso
	void *puntero = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(puntero == MAP_FAILED) {
		printf("Mapeo fallido\n");
		return -1;
	}

	// Colocar la imagen fusionada en la memoria compartida
	memcpy(puntero, fusionada, SIZE);

	return 0;

}
