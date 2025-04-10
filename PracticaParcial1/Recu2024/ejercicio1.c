#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void primos() {
    int num = 2;
    while(1) {
        int esPrimo = 1;  // Supongo que es primo
        if (num <= 1) {
            esPrimo = 0;
        } else if (num > 2 && (num % 2 == 0)) {
            esPrimo = 0;      // Si es par, no es primo
        } else {
            int i = 3;
            while (esPrimo && (i * i <= num)) {
                // Verifico hasta la raiz cuadrada de numero
                if (num % i == 0) {
                    esPrimo = 0;  // Si es divisible por i, entonces no es primo
                }
                i = i + 2;  // Solo evaluo los impares
            }
        }
        if(esPrimo) {
            printf("Soy el proceso 1. Numero primo: %d\n", num);
        }
        num++;
        usleep(20000);  // 20 ms
    }
}

void bisiestos() {
    int num = 0;
    while(1) {
        if(((num % 4 == 0) && (num % 100 != 0)) || (num % 400 == 0)) {
            printf("Soy el proceso 2. Numero bisiesto: %d\n", num);
        }
        num++;
        usleep(20000);  // 20 ms
    }
}

int main() {
    int pid1 = fork();

    if(pid1 == 0) {
        printf("Proceso hijo 1 iniciado. Calcula primos infinitamente\n");
        primos();
    } else {
        int pid2 = fork();
        if(pid2 == 0) {
            printf("Proceso hijo 2 iniciado. Calcula bisiestos infinitamente\n");
            bisiestos();
        } else {
            sleep(4);
            kill(pid2, SIGKILL);
            printf("Proceso padre finalizo el proceso 2 (bisiestos)\n");
            sleep(4);
            kill(pid1, SIGKILL);
            printf("Proceso padre finalizo el proceso 1 (primos)\n");
            exit(0);
        }
    }

    return 0;
}
