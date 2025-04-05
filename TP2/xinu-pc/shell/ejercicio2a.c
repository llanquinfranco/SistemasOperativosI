#include <xinu.h>

void calcularPrimos(int, int);
int esPrimo(int);

void ejercicio2a() {

    int pid1;
    int pid2;

    pid1 = create(calcularPrimos, 2048, 20, "Proceso 1", 2, 1, 5000);
    pid2 = create(calcularPrimos, 2048, 20, "Proceso 2", 2, 5000, 10000);

    resume(pid1);
    resume(pid2);

}

void calcularPrimos(int minimo, int maximo) {
    printf("Proceso iniciado\n");
    for(int i = minimo; i <= maximo; i++) {
        if(esPrimo(i) == 1) {
            printf("%d\n", i);
        }
    }
    printf("Proceso finalizado\n");
}

int esPrimo(int numero) {
    int primo = 1;  // Supongo que es primo

    if (numero <= 1) {
        primo = 0;
    } else if (numero > 2 && (numero % 2 == 0)) {
        primo = 0;      // Si es par, no es primo
    } else {
        int i = 3;
        while (primo && (i * i <= numero)) {
            // Verifico hasta la raiz cuadrada de numero
            if (numero % i == 0) {
                primo = 0;  // Si es divisible por i, entonces no es primo
            }
            i = i + 2;  // Solo evaluo los impares
        }
    }

    return primo;
}