#include <stdio.h>
#include <stdlib.h>

#define N 240000
#define BSIZE 4096
#define SMALL 4

char *pp;

int main() {
    int i, j, k;

    printf("Direccion virtual de main(): %p\n", &main);
    printf("Direccion virtual de variable i: %p\n", &i);
    printf("Direccion virtual de variable j: %p\n", &j);

    pp = malloc(N * BSIZE);
    if(pp == NULL) {
        printf("Error al reservar memoria\n");
        exit(1);
    }

    // Recorremos y verificamos todo el segmento solicitado
    for(j = 0; j < BSIZE; j++) {
        for(i = 0; i < N; i++) {
            *(pp + i * BSIZE + j) = 2;  // pp[i][j] = 2
        }
    }

    // Recorremos y verificamos que hemos modificado todo el segmento solicitado
    for(i = 0; i < N; i++) {
        for(j = 0; j < BSIZE; j++) {
            if(*(pp + i * BSIZE + j) != 2) {    // if pp[i][j] != 2
                printf("ERROR\n");
                exit(1);
            }
        }
    }

    printf("OK\n");
    return 0;
}