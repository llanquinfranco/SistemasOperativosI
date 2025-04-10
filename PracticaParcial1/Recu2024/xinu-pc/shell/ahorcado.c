#include <xinu.h>

void entrada();
void computo();
void visual();
void fin(int, int, int, int);
int verificar(char letra, char *palabra, char *adivinada);

char acertijo[] = "linux";
char aux[] = "-----";
int intentos = 6;
int encontrada = 0;
int c;
int hayEntrada = 0;

void ahorcado() {

    int pidMain = getpid();
    int pidE = create(entrada, 1024, 20, "entrada", 0);
    int pidC = create(computo, 1024, 20, "computo", 0);
    int pidV = create(visual, 1024, 20, "visual", 0);
    int pidF = create(fin, 1024, 20, "fin", 4, pidE, pidC, pidV, pidMain);

    resume(pidE);
    resume(pidC);
    resume(pidV);
    resume(pidF);
    
    control(CONSOLE, TC_MODER, 0, 0);

    receive();  // Espera la señal de fin de juego

    control(CONSOLE, TC_MODEC, 0, 0);  // Restaurar modo normal del shell
    exit();  // Finaliza el proceso principal
}

void entrada() {
    while(1) {
        if(!hayEntrada) {
            printf("\n\r c = %c  Ingrese una letra (0 para salir) (%s) (%d intentos restantes): ", c, aux, intentos);
            c = getchar();
            if (c == '0') {
                /* salir */
                hayEntrada = 1;
                break;
            }
            hayEntrada = 1;
        }
    }
}

void computo() {
    while(1) {
        while (hayEntrada && (intentos > 0) && !encontrada) {
            if (verificar(c, acertijo, aux)) {
                printf("\n\r Acierto! La letra %c ha sido encontrada\n", c);
                if (strcmp(acertijo, aux) == 0) {
                    encontrada = 1;
                }
            } else {
                printf("\n\r La letra %c no ha sido encontrada\n", c);
                intentos--;
            }
            hayEntrada = 0;
        }
    }
}

void visual() {
    while(1) {
        sleep(1);
        printf("\n\r Palabra: %s | Intentos: %d\n", aux, intentos);
    }
}

void fin(int pidE, int pidC, int pidV, int pidMain) {
    while(1) {
        sleep(2);
        if (intentos == 0) {
            printf("\n\r Perdiste, la palabra era linux.\n");
            kill(pidE);
            kill(pidC);
            kill(pidV);
            break;
        } else if (encontrada) {
            printf("\n\r Ganaste, la palabra es linux!\n");
            kill(pidE);
            kill(pidC);
            kill(pidV);
            break;
        }
    }
    printf("\n\r Juego terminado. Volviendo al shell\n");
    control(CONSOLE, TC_MODEC, 0, 0);
    send(pidMain, 1); // Aviso al proceso padre que termine
    exit();
}

int verificar(char letra, char *palabra, char *adivinada)
{
	int acierto = 0;
	for (int i = 0; i < 5; i++) {
		if (palabra[i] == letra) {
			adivinada[i] = letra;
			acierto = 1;
		}
	}
	return acierto;
}