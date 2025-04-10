#include <xinu.h>

extern calcularPrimos(int, int);    // Solo declaro los metodos de los procesos ¿?
void calcularConSleep(int, int);    // xq con esPrimo() no me hizo drama y esta arafue

void ejercicio2c() {

    int pid1;
    int pid2;

    pid1 = create(calcularConSleep, 2048, 25, "Proceso 1", 2, 1, 5000);
    pid2 = create(calcularPrimos, 2048, 20, "Proceso 2", 2, 5000, 10000);

    resume(pid1);
    resume(pid2);

}

void calcularConSleep(int minimo, int maximo) {
    int contador = 0;
    printf("Proceso iniciado\n");
    for(int i = minimo; i <= maximo; i++) {
        if(esPrimo(i) == 1) {
            printf("%d\n", i);
            contador++;
        }
        if(contador == 100) {
            sleepms(10);
        }
    }
    printf("Proceso finalizado\n");

}
