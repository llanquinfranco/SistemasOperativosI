#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 100

int pos = 0;
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

int main() {
    int c;
    system("/bin/stty raw");
    printf("\n\r Ingrese un caracter. ENTER para finalizar: ");
    c = getchar();
    while(c != 13 && pos < (MAXIMO - 1)) {
        if(c != ' ') {
            cadena[pos] = c;
            pos++;
            
        }
        printf("\n\r Ingrese un caracter. ENTER para finalizar: ");
        c = getchar();
    }
    system("/bin/stty sane erase ^H");
    cadena[pos] = '\0';
    printf("\n\n\r Cadena ingresada: %s\n", cadena);
    if(esPalindromo(cadena, pos) == 1) {
        printf("\n\r La cadena SI es palindromo/capicua\n\n");
    } else {
        printf("\n\r La cadena NO es palindromo/capicua\n\n");
    }
    return 0;
}
