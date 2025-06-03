#include <stdio.h>
#include <stdlib.h>     // malloc(), exit()
#include <fcntl.h>      // open(), constantes O_
#include <unistd.h>     // read(), close()

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
        estado = read(fd, &caracter, 1);    // El puntero interno de fd avanza 1 caracter en cada iteracion
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
    // a. Leer contenido de principe_y_mendigo.txt, y colocarlo en memoria dinamica
    const char *rutaArchivo = "/home/fran/Escritorio/22 - Sistemas Operativos I (2025)/TP/Codigos/PracticaParcial2/Parcial2022/principe_y_mendigo.txt";
    int tamanioArchivo = obtenerTamanio(rutaArchivo);

    // Reabrir archivo para leer su contenido
    int fd = open(rutaArchivo, O_RDONLY);
    if (fd == -1) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    // Reservar espacio dinamicamente
    char *puntero = malloc(tamanioArchivo); // Puntero apunta al principio de la memoria reservada (siempre)
    if (puntero == NULL) {
        close(fd);
        printf("Error al reservar memoria dinamicamente\n");
        return -1;
    }

    // Leer el contenido completo del archivo y almacenarlo en memoria dinamica
    int estado = read(fd, puntero, tamanioArchivo);
    if(estado < 0) {
        free(puntero);
        close(fd);
        printf("Error al leer el archivo\n");
        return -1;
    }

    close(fd);

    // b. Demuestre que en la posición nro 65512 del archivo se encuentre la palabra “Catalina”.
    int pos = 65512;
    char nombre[] = "Catalina";
    int coincide = 1;
    // Verifico que se encuentra la palabra
    for(int i = 0; i < 8; i++) {
        if(puntero[pos + i] != nombre[i]) {
            coincide = 0;
            break;
        }
    }
    // Una vez alcanzada esa posición mostrar los siguientes 8 bytes en pantalla.
    if(coincide) {
        for(int i = 0; i < 8; i++) {
            printf("%c", puntero[pos + i]);
        }
        printf("\n");
    } else {
        printf("NO se encuentra la palabra 'Catalina'\n");
        free(puntero);
        return -1;
    }

    // c. Presente las direcciones de memoria virtual de los segmentos del programa
    printf("Direccion de memoria virtual de main(): %p\n", &main);
    printf("Direccion de memoria virtual reservada: [%p - %p] \n", puntero, puntero + tamanioArchivo);
    // Direccion de memoria virtual de main(): 0x55f220450339                       Segmento de texto
    // Direccion de memoria virtual reservada: [0x7a6f8b443010 - 0x7a6f8b4a08e5]    Heap

    free(puntero);

    return 0;
}
