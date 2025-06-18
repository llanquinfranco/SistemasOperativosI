#include <xinu.h>

void entrada(int);
void computo();

#define MAXIMO 100

int c;
int pos;
char cadena[MAXIMO];

int esPalindromo(char cadena[], int pos) {
    int i = 0;
    int j = pos - 1;
    int seCumple = 1;

    while ((i < j) && (seCumple == 1)) {
        if (cadena[i] == cadena[j]) {
            i++;
            j--;
        } else {
            seCumple = 0;
        }
    }

    return seCumple;
}

void entrada(int pidMain) {
    pos = 0;
    kprintf("\n\r Ingrese un caracter. ENTER para finalizar: ");
    c = getchar();
    kprintf("%c", c);
    while(c != 13 && pos < (MAXIMO - 1)) {
        if(c != ' ') {
            cadena[pos] = c;
            pos++;
            
        }
        kprintf("\n\r Ingrese un caracter. ENTER para finalizar: ");
        c = getchar();
        kprintf("%c", c);
    }
    cadena[pos] = '\0';
    send(pidMain, 1);
    exit();
}

void computo(char cadena[], int pos, int pidMain) {
    printf("\n\n\r Cadena ingresada: %s\n", cadena);
    if(esPalindromo(cadena, pos) == 1) {
        printf("\n\r La cadena SI es palindromo/capicua\n\n");
    } else {
        printf("\n\r La cadena NO es palindromo/capicua\n\n");
    }
    send(pidMain, 1);
    exit();
}

void palindromo() {

    int pidMain = getpid();

    int pidA = create(entrada, 2048, 20, "Proceso A", 1, pidMain);
    resume(pidA);

    control(CONSOLE, TC_MODER, 0, 0);

    receive();

    control(CONSOLE, TC_MODEC, 0, 0);

    int pidB = create(computo, 2048, 20, "Proceso B", 3, cadena, pos, pidMain);
    resume(pidB);

    receive();

    exit();
}

