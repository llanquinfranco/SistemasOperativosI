#include <xinu.h>

int ahorcado() {

    int c, intentos = 5, aciertos = 0, exito;
    char palabra[] = "sistemasoperativosi";
    int longitud = strlen(palabra);
    char oculta[longitud + 1];

    // Inicializar la palabra oculta con guiones
    for (int i = 0; i < longitud; i++) {
        oculta[i] = '_';
    }
    oculta[longitud] = '\0';

    while (intentos > 0) {
        
        printf("Ingrese una letra (0 para salir): ");
        c = getchar();
        while (getchar() != '\n');  // Limpiar el búfer de entrada

        if (c == '0') {
            printf("Salió del juego\n");
            break;
        } else {
            // Comprobamos
            exito = 0;
            int i = 0;
            while (palabra[i] != '\0') {
                if (palabra[i] == c) {
                    oculta[i] = c;
                    exito = 1;
                    aciertos++;
                }
                i++;
            }
        }
        
        if (aciertos == longitud) {
            printf("Ganaste, la palabra es: %s\n", palabra);
            break;
        }

        if (exito == 0) {
            intentos--;  // Se reduce el intento solo si falló
            printf("Erraste: %s\n", oculta);
            printf("Te quedan %d vidas\n\n", intentos);
        } else {
            printf("Acertaste: %s\n", oculta);
            printf("Te quedan %d vidas\n\n", intentos);
        }

    }

    if (intentos == 0) {
        printf("Perdiste, la palabra era: %s\n", palabra);
    }

    return 0;
}

/* Decirle al sistema que el modo input es RAW */
// control(CONSOLE, TC_MODER, 0, 0);
// control(CONSOLE, TC_MODEC, 0, 0);