#include <stdio.h>
#include <stdlib.h>     // malloc(), exit()
#include <fcntl.h>      // open(), constantes O_
#include <unistd.h>     // read(), close()

#define ENCABEZADO 15

int obtenerTamanio(const char rutaDeArchivo[]) {
    int tamanio = 0;
    int estado;
    char caracter;

    // Abrir el archivo solo para lectura
    int fd = open(rutaDeArchivo, O_RDONLY);
    if(fd == -1) {
        printf("Error al abrir el archivo\n");
        exit(-1);
    }

    // Contar caracter por caracter
    while(1) {
        estado = read(fd, &caracter, 1);
        if(estado == -1) {
            close(fd);
            printf("Error al leer el archivo\n");
            exit(-1);
        } else if(estado == 0) {
            break;  // Llego hasta el final
        } else {
            tamanio++;
        }
    }

    close(fd);
    return tamanio;
}

int main() {
    const char *rutaArchivo = "/home/fran/Escritorio/22 - Sistemas Operativos I (2025)/TP/Codigos/PracticaParcial2/Parcial2023/cat.pgm";
    int tamanioArchivo = obtenerTamanio(rutaArchivo);

    // Rebrir el archivo para leer su contenido
    int fd = open(rutaArchivo, O_RDONLY);
    if(fd == -1) {
        printf("Error al abrir el archivo\n");
        exit(-1);
    }

    sleep(10);
    // Reservar memoria dinamicamente
    char *puntero = malloc(tamanioArchivo);
    if(puntero == NULL) {
        close(fd);
        printf("Error al reservar memoria dinamicamente\n");
        return -1;
    }
    printf("123\n");
    sleep(10);

    // Leer el contenido completo del archivo y almacenarlo en memoria dinamica
    int estado = read(fd, puntero, tamanioArchivo);
    if(estado < 0) {
        free(puntero);
        close(fd);
        printf("Error al leer el archivo\n");
        return -1;
    }

    close(fd);

    // Creo un arreglo y guardo el encabezado
    unsigned char imagenNueva[tamanioArchivo];
    for(int i = 0; i < ENCABEZADO; i++) {
        imagenNueva[i] = puntero[i];
    }
    // Ahora guardo los pixeles invertidos
    int j = ENCABEZADO;
    for(int i = tamanioArchivo - 1; i >= ENCABEZADO; i--) {
        imagenNueva[j] = puntero[i];
        j++;
    }

    // Ahora creo el archivo nuevo
    const char *nuevo = "/home/fran/Escritorio/22 - Sistemas Operativos I (2025)/TP/Codigos/PracticaParcial2/Parcial2023/cat2.pgm";
    fd = open(nuevo, O_RDWR | O_CREAT | O_TRUNC, 0666);     // Le pide al sistema operativo crear un archivo nuevo
    write(fd, &imagenNueva[0], tamanioArchivo);

    // b. Agregue sentencias para que emita la direccion virtual
    printf("Direccion virtual del inicio del segmento de memoria dinamico: %p\n", puntero);




    free(puntero);
    return 0;
}