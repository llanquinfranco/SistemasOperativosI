/* primos entre el numero 1 y MAX */
#include <xinu.h>

int encontrar_primos(int, int);

#define MAX 500000

int total = 0;

void controlProcesos() {

    int pid1 = create(encontrar_primos, 1024, 20, "Proceso 1", 2, 0, 5000);
    int pid2 = create(encontrar_primos, 1024, 80, "Proceso 2", 2, 5001, 9999);

    resume(pid1);
    resume(pid2);

}

int encontrar_primos(int from, int to) {
    int i, n, primo;

    for (i = from; i <= to; i++) {
        primo = 1;
        n = 2;

        while (n <= i / 2 && primo) {
            if (i % n == 0) {
                primo = 0;
            }
            n++;
        }

        if (primo) {
            printf("%d ", i);
        }
    }
    total++;
    return 0;
}

