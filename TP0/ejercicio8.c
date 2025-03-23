#include <stdio.h>

int main() {
    printf("El tamaño de char es: %zu bytes\n", sizeof(char));
    printf("El tamaño de int es: %zu bytes\n", sizeof(int));
    printf("El tamaño de long es: %zu bytes\n", sizeof(long));
    printf("El tamaño de float es: %zu bytes\n", sizeof(float));
    printf("El tamaño de double es: %zu bytes\n", sizeof(double));
    return 0;
}