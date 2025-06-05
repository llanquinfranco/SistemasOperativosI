#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>   // Para constantes mode
#include <fcntl.h>      // Para constantes O_*
#include <unistd.h>     // Para ftruncate(), read(), close()

int obtenerTamanio(const char rutaArchivo[]) {
    int tamanioArchivo = 0;
    int estado;
    char c;

    // Abrir el archivo solo de lectura
    int fd = open(rutaArchivo, O_RDONLY);
    if(fd == -1) {
        printf("Error al abrir archivo (Programa 2)\n");
        exit(-1);
    }

    // Contar caracter por caracter
    while(1) {
        estado = read(fd, &c, 1); // ← ACÁ estaba el error: usabas == en vez de =
        if(estado == -1) {
            printf("Error al leer archivo (Programa 2)\n");
            exit(-1);
        } else if(estado == 0) {
            break;
        } else {
            tamanioArchivo++;
        }
    }

    close(fd);
    return tamanioArchivo;
}

// El segundo programa ordena los números
int main() {
    const char *ruta = "desordenado.bin";
    const char *segmento = "PARCIAL";
    int cantEnteros = obtenerTamanio(ruta) / sizeof(int);   // 1000
    int tamanioTotal = (cantEnteros + 1) * sizeof(int);     // 4004

    // Abrir el segmento de memoria compartida
    int shm_fd = shm_open(segmento, O_RDWR, 0666);
    if(shm_fd == -1) {
        printf("Error al abrir el segmento de memoria compartida (Programa 2)\n");
        exit(-1);
    }

    // Mapear el segmento de memoria compartida
    int *puntero = mmap(0, tamanioTotal, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(puntero == MAP_FAILED) {
        printf("Mapeo fallido (Programa 2)\n");
        exit(-1);
    }

    // Esperar que el primer valor sea distinto de cero
    while(puntero[0] == 0) {
        // Espera activa
    }

    // Ordenar con burbuja
    int n = puntero[0];
    int i, j, aux;
    for(i = 1; i < n; i++) {
        for(j = 1; j < n - (i - 1); j++) {
            if(puntero[j] > puntero[j + 1]) {
                aux = puntero[j];
                puntero[j] = puntero[j + 1];
                puntero[j + 1] = aux;
            }
        }
    }

    // Avisar al otro proceso que terminó
    puntero[0] = 1;

    return 0;
}
