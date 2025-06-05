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
        printf("Error al abrir archivo (Programa 1)\n");
        exit(-1);
    }

    // Contar caracter por caracter
    while(1) {
        estado = read(fd, &c, 1); // El puntero interno de fd avanza 1 caracter en cada iteracion
        if(estado == -1) {
            printf("Error al leer archivo (Programa 1)\n");
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

/* El primer programa lee el contenido de un archivo llamado desordenado.bin, en donde existen
números enteros, y los coloca en un segmento de memoria compartida. */
int main() {
    const char *ruta = "desordenado.bin";
    const char *segmento = "PARCIAL";
    int cantEnteros = obtenerTamanio(ruta) / sizeof(int);   // 1000
    int tamanioTotal = (cantEnteros + 1) * sizeof(int);     // 4004


    // Crear el segmento de memoria compartida
    int shm_fd = shm_open(segmento, O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1) {
        printf("Error al crear el segmento de memoria compartida (Programa 1)\n");
        return -1;
    }

    // Configurar el tamaño del segmento de memoria compartida
    if (ftruncate(shm_fd, tamanioTotal) == -1) {
        printf("Error al establecer tamaño de memoria compartida (Programa 1)\n");
        return -1;
    }

    // Mapear el segmento de memoria compartida en el espacio de direccion del proceso
    int *puntero = mmap(0, tamanioTotal, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(puntero == MAP_FAILED) {
        printf("Mapeo fallido (Programa 1)\n");
        return -1;
    }

    // Luego de crear la memoria compartida, coloca el entero cero (0) en el primer lugar
    puntero[0] = 0;

    // Reabrir el archivo para leer su contenido
    int file_fd = open(ruta, O_RDONLY);
    if(file_fd == -1) {
        printf("Error al reabrir archivo (Programa 1)\n");
        return -1;
    }

    // Leer el contenido del archivo y copiarlo al segmento de memoria compartida
    ssize_t bytesLeidos = read(file_fd, &puntero[1], cantEnteros * sizeof(int));
    if (bytesLeidos == -1) {
        printf("Error al leer el archivo (Programa 1)\n");
        return -1;
    }

    // Cerrar el archivo
    if(close(file_fd) == -1) {
        printf("Error al cerrar el archivo (Programa 1)\n");
    }

    // Cuando termina de cargar la memoria, coloca en el primer lugar el entero n
    puntero[0] = cantEnteros;

    // Se quedará esperando de manera activa a que en el primer lugar aparezca el uno (1)
    while(puntero[0] != 1) {
        // Espera activa
    }

    // Cuando ese lugar sea 1, guardar los números en ordenado.bin
    int fd = open("ordenado.bin", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        printf("Error al crear el archivo ordenado.bin (Programa 1)\n");
        exit(-1);
    }

    // Escribo los enteros ordenados
    write(fd, &puntero[1], cantEnteros * sizeof(int));

    // Cerrar archivo
    close(fd);

    // Eliminar el segmento de memoria compartida
    if(shm_unlink(segmento) == -1) {
        printf("Error al remover el segmento de memoria compartida (Programa 1)\n");
        exit(-1);
    }

    return 0;
}
