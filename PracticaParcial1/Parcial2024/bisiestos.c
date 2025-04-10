#include <stdio.h>

void calcularBisiestos(int min, int max, int numProceso) {
    int i;
    for(i = min; i <= max; i++) {
        if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
            printf("Hijo %d, año bisiesto n° %d\n", numProceso, i);
        }
    }
}

int main() {
    int pid1, pid2;

    pid1 = fork();
    if(pid1 == 0) {  // Proceso hijo 1 (Siempre el nuevo hijo es pid=0)
        calcularBisiestos(0, 2000, 1);
        printf("Proceso hijo 1 finalizado\n");
    } else {
        pid2 = fork();
        if(pid2 == 0) { // Proceso hijo 2 (Siempre el nuevo hijo es pid=0)
            calcularBisiestos(2001, 4000, 2);
            printf("Proceso hijo 2 finalizado\n");
        } else {    // Proceso padre
            wait(NULL);
            wait(NULL); // Espera a que terminen los 2 hijos, sin sleep
            printf("Proceso padre finalizado\n");
        }
    }
    return 0;
}