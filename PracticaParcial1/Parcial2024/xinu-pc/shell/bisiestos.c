/* bisiestos.c en XINU */
#include <xinu.h>

#define ASCII_ESC 27
long int calculo[2];
int c;

/* completar el codigo del programa bisiesto */
bisiesto(int base, int limite, int n) {
    int i;
    /* base, limite y n vienen como argumentos */
    for (i = base; i <= limite; i++) {
        if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
            calculo[n] = i;
            sleepms(300);
        }
    }
}

muestra_bisiestos() {
    /* limpiar toda la pantalla */
    printf("%c[2J", ASCII_ESC);

    while (1) {
        /* Nos posicionamos en la fila 5 columna 10 */
        printf("%c[5;10f", ASCII_ESC);
        printf("proceso a: %d \n", calculo[0]);

        /* Nos posicionamos en la fila 6 columna 10 */
        printf("%c[7;10f", ASCII_ESC);
        printf("proceso b: %d \n", calculo[1]);

        sleepms(50);
    }
}

/* completar el gestor de procesos bisiestos */
gestor_bisiestos() {

    int pid1 = create(bisiesto, 8192, 20, "Proceso hijo 1", 3, 0, 2000, 0);
    int pid2 = create(bisiesto, 8192, 20, "Proceso hijo 2", 3, 2001, 4000, 1);
    int pidM = create(muestra_bisiestos, 8192, 20, "Proceso muestra_bisiestos", 0);

    resume(pid1);
    resume(pid2);
    resume(pidM);

    int estadoHijo1 = 1;    // Estado 0 = suspendido, 1 = activo, -1 = muerto
    int estadoHijo2 = 1;    

    control(CONSOLE, TC_MODER, 0, 0);

    while (1) {
        /* gestionar las pulsaciones del teclado, procesar, informar al usuario */
        c = getchar();
        switch (c) {
            case '1':   // El primer proceso se suspende/reanuda
                if (estadoHijo1 == -1) {
                    printf("%c[9;10f", ASCII_ESC );
                    printf("primer proceso ya finalizado\n");
                } else if(estadoHijo1 == 1) {
                    estadoHijo1 = 0;
                    while (suspend(pid1) == SYSERR) {
                        // Espera hasta que sea suspendible
                    }
                    printf("%c[9;10f", ASCII_ESC );
                    printf("primer proceso suspendido\n");
                } else {
                    estadoHijo1 = 1;
                    resume(pid1);
                    printf("%c[9;10f", ASCII_ESC );
                    printf("primer proceso reanudado\n");
                }
            break;

            case '3':   // El primer proceso debe ser finalizado
                if(estadoHijo1 != -1) {
                    estadoHijo1 = -1;
                    kill(pid1);
                    printf("%c[9;10f", ASCII_ESC);
                    printf("primer proceso finalizado\n");
                }
            break;

            case '7':   // El segundo proceso se suspende/finaliza
                if(estadoHijo2 == -1) {
                    printf("%c[11;10f", ASCII_ESC );
                    printf("segundo proceso ya finalizado\n");
                } else if(estadoHijo2 == 1) {
                    estadoHijo2 = 0;
                    while (suspend(pid2) == SYSERR) {
                        // Espera hasta que sea suspendible
                    }
                    printf("%c[11;10f", ASCII_ESC );
                    printf("segundo proceso suspendido\n");
                } else {
                    estadoHijo2 = 1;
                    resume(pid2);
                    printf("%c[11;10f", ASCII_ESC);
                    printf("segundo proceso reanudado\n");
                }
            break;

            case '9':   // El segundo proceso debe ser finalizado
                if(estadoHijo2 != -1) {
                    estadoHijo2 = -1;
                    kill(pid2);
                    printf("%c[11;10f", ASCII_ESC);
                    printf("segundo proceso finalizado\n");
                }
            break;

            case 'q':   // Finaliza todos los procesos y vuelve al shell
                kill(pid1);
                kill(pid2);
                kill(pidM);
                printf("%c[13;10f", ASCII_ESC);
                printf("Todos los procesos finalizados. Volviendo al shell\n");
                control(CONSOLE, TC_MODEC, 0, 0);
                exit();
            break;
            
            default:
            break;
        }
        sleepms(5);
    }
}