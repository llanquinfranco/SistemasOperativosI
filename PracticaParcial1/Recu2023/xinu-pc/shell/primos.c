/* primos entre el numero 1 y MAX */
#include <xinu.h>

int encontrar_primos(int, int, int);
void controlProcesos();
//void planificador(int, int, int, int);
//void cambiarPrioridad(int, int, int);

#define MAX 500000

int total = 0;

void primos() {
    int pidC = create(controlProcesos, 1024, 20, "Control", 2, 0, 5000);
    resume(pidC);
}

void controlProcesos() {

    int pid1 = create(encontrar_primos, 1024, 20, "Proceso 1", 3, 0, 5000, 1);
    int pid2 = create(encontrar_primos, 1024, 20, "Proceso 2", 3, 5001, 9999, 2);

    resume(pid1);
    resume(pid2);
    
    // Creo el planificador con mas prioridad para que pueda manejar los procesos
    //int pidP = create(planificador, 1024, 20, "Planificador", 4, pid1, 200, pid2, 800);
    //resume(pidP);

}

int encontrar_primos(int from, int to, int hijo) {
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
        // Simula el uso desigual de CPU
        if (hijo == 1) {
            // Este duerme más (80ms) => menos CPU (20%)
            sleepms(80);
        } else {
            // Este duerme menos (20ms) => más CPU (80%)
            sleepms(20);
        }
    }
    total++;
    return 0;
}

/*
void planificador(int pid1, int tiempo1, int pid2, int tiempo2) {
    int pidPlanificador = getpid();
    int prioridadPlanificador = getprio(pidPlanificador);
    while(1) {
        cambiarPrioridad(pid1, tiempo1, prioridadPlanificador); // 200ms para proceso 1 (20%)
        cambiarPrioridad(pid2, tiempo2, prioridadPlanificador); // 800ms para proceso 2 (80%)
    }
}

void cambiarPrioridad(int pidProceso, int tiempo, int prioridadPlanificador) {
    int prioridadOriginal = getprio(pidProceso);
    // Le damos mas prioridad para que corra
    chprio(pidProceso, prioridadPlanificador - 1);
    // El planificador se suspende y el pidProceso toma la CPU
    sleepms(tiempo);
    // Restauramos la prioridad original
    chprio(pidProceso, prioridadOriginal);
}
*/