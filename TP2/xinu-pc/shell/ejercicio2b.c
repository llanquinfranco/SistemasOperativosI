#include <xinu.h>

extern calcularPrimos(int, int);

void ejercicio2b() {

    int pid1;
    int pid2;

    pid1 = create(calcularPrimos, 2048, 25, "Proceso 1", 2, 1, 5000);
    pid2 = create(calcularPrimos, 2048, 20, "Proceso 2", 2, 5000, 10000);

    resume(pid1);
    resume(pid2);

}
