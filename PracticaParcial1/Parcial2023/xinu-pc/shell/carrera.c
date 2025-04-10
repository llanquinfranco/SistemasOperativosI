#include <xinu.h>

#define ASCII_ESC 27

int c;
int vel_a = 0;
int vel_b = 0;

void corredor_a() {
	while(1) {
		vel_a++;
	}
}

void corredor_b() {
	while(1) {
		vel_b++;
	}
}

void muestra_carrera() {
	/* limpiar toda la pantalla */
	printf( "%c[2J", ASCII_ESC );

	while(1) {
		/* Nos posicionamos en la fila 5 columna 10 */
    		printf( "%c[5;10f", ASCII_ESC );
    		printf( "Velocidad corredor A: %d \n", vel_a);

		/* Nos posicionamos en la fila 6 columna 10 */
    		printf( "%c[6;10f", ASCII_ESC );
    		printf( "Velocidad corredor B: %d \n", vel_b);

		sleepms(50);
	}
}

void control_race() {

    int pidA = create(corredor_a, 2048, 20, "Corredor A", 0);
    int pidB = create(corredor_b, 2048, 20, "Corredor B", 0);
    int pidM = create(muestra_carrera, 2048, 20, "Muestra carrera", 0);

    resume(pidA);
    resume(pidB);
    resume(pidM);

    int estadoProcesoA = 1; // Estado 0 = suspendido, 1 = activo, -1 = muerto
    int estadoProcesoB = 1;

    control(CONSOLE, TC_MODER, 0, 0);

    while(1) {
        // Gestionar pulsaciones del teclado
        c = getchar();
        switch (c) {
            case '1':   // el proceso corredor_a se suspende/reanuda
                if (estadoProcesoA == -1) {
                    printf("%c[9;10f", ASCII_ESC );
                    printf("Corredor A ya finalizado");
                } else if (estadoProcesoA == 0) {
                    estadoProcesoA = 1;
                    resume(pidA);
                    printf("%c[9;10f", ASCII_ESC );
                    printf("Corredor A reanudado");
                } else {
                    estadoProcesoA = 0;
                    while (suspend(pidA) == SYSERR) {
                        // Espera hasta que sea suspendible
                    }
                    printf("%c[9;10f", ASCII_ESC );
                    printf("Corredor A suspendido");
                }
            break;

            case '5':   // el proceso corredor_a muere
                if(estadoProcesoA != -1) {
                    estadoProcesoA = -1;
                    kill(pidA);
                    printf("%c[9;10f", ASCII_ESC );
                    printf("Corredor A finalizado");
                }
            break;

            case '2':   // el proceso corredor_b se suspende/reanuda
                if (estadoProcesoB == -1) {
                    printf("%c[11;10f", ASCII_ESC );
                    printf("Corredor B ya finalizado");
                } else if (estadoProcesoB == 0) {
                    estadoProcesoB = 1;
                    resume(pidB);
                    printf("%c[11;10f", ASCII_ESC );
                    printf("Corredor B reanudado");
                } else {
                    estadoProcesoB = 0;
                    while (suspend(pidB) == SYSERR) {
                        // Espera hasta que sea suspendible
                    }
                    printf("%c[11;10f", ASCII_ESC );
                    printf("Corredor B suspendido");
                }
            break;

            case '6':   // el proceso corredor_b muere.
                if(estadoProcesoB != -1) {
                    estadoProcesoB = -1;
                    kill(pidB);
                    printf("%c[11;10f", ASCII_ESC );
                    printf("Corredor B finalizado");
                }
            break;

            case '0':   // salir xd
                kill(pidA);
                kill(pidB);
                kill(pidM);
                printf("%c[13;10f", ASCII_ESC );
                printf("Todos los procesos finalizados. Volviendo al shell\n");
                control(CONSOLE, TC_MODEC, 0, 0);
                exit();
            break;
        
            default:
            break;
        }
    }
}
