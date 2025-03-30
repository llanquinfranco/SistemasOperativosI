#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    int pid;

    pid = fork();               // Crea un nuevo proceso

    if (pid == 0) {             // Proceso hijo
        printf("Proceso hijo iniciado\n");
        execl("/usr/bin/date", "date", NULL);
        exit(0);
    } else {                    // Proceso padre
        printf("Proceso padre iniciado\n");
        sleep(2);               // Espera a que el proceso hijo haga lo suyo
        printf("Proceso padre finalizado\n");
        exit(0);                 // Finaliza con exit()
    }

    return 0;
}

/*

Funciones que realizaron llamadas al sistema:
- fork(): clona el proceso padre, creando una copia exacta
- execl(): reemplaza el proceso actual con una nueva imagen de proceso
- sleep(): pausa la ejecucion de un proceso durante unos segundos
- exit(): finaliza un proceso

*/