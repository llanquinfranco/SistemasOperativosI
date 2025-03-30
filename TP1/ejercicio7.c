#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

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

int obtenerPrimosHijo() {
    for(int i = 1000; i <= 5000; i++) {
        if(esPrimo(i)) {
            printf("Hijo: %d\n", i);
        }
    }
    return 0;
}

int obtenerPrimosPadre() {
    for(int i = 0; i <= 1000; i++) {
        if(esPrimo(i)) {
            printf("Padre: %d\n", i);
        }
    }
    return 0;
}

int main() {
    int pid;

    pid = fork();               // Crea un nuevo proceso

    if (pid == 0) {             // Proceso hijo
        printf("Proceso hijo iniciado\n");
        obtenerPrimosHijo();
        printf("Proceso hijo finalizado\n");
        exit(0);
    } else {                    // Proceso padre
        printf("Proceso padre iniciado\n");
        obtenerPrimosPadre();
        printf("Proceso padre finalizado\n");
        kill(pid, SIGKILL);     // Finaliza el proceso hijo
        printf("Maté a mi propio hijo (suena horrible)\n");
        exit(0);                 // Finaliza con exit()
    }

    return 0;
}

/*
 
Padre: 991
Hijo: 2113
Padre: 997
Hijo: 2129
Proceso padre finalizado
Hijo: 2131
Hijo: 2137
Maté a mi propio hijo (suena horrible)

No le fue posible calcular todos los que debia calcular ya que el 
proceso padre termino antes de que el proceso hijo llegue a 5000

*/