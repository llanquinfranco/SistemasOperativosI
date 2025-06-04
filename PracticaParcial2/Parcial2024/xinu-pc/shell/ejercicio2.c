#include <xinu.h>

#define NO_ES_PRIMO 0
#define ES_PRIMO 1
#define NO_ES_BISIESTO 2
#define ES_BISIESTO 3

void reportar(int mensaje);
void proceso2(int pidPrincipal);
void proceso3(int pidPrincipal);

void ejercicio2() {

    int pid1 = getpid();
    int pid2 = create(proceso2, 2048, 20, "Proceso 2", 1, pid1);
    int pid3 = create(proceso3, 2048, 20, "Proceso 3", 1, pid1);

    resume(pid2);
    resume(pid3);

    int i;
    char buf[10];

    printf("INGRESE UN NUMERO: ");

    read(CONSOLE, buf, 10);
    i = atoi(buf);

    // Limpiar el buzon de mensajes para evitar basura previa
    recvclr();

    // Enviar la entrada del usuario a los procesos
    send(pid2, i);
    send(pid3, i);

    // Reportar si el número ingresado por el usuario es primo y/o año bisiesto
    int reporte1 = receive();
    reportar(reporte1);
    int reporte2 = receive();
    reportar(reporte2);
}

void reportar(int mensaje) {
    switch (mensaje) {
        case 0:
            printf("El numero NO es primo\n");
            break;
        case 1:
            printf("El numero es primo\n");
            break;
        case 2:
            printf("El numero NO es bisiesto\n");
            break;
        case 3:
            printf("El numero es bisiesto\n");
            break;
    }

}

void proceso3(int pidPrincipal) {
    // Verifica si el número es un año bisiesto y reporta el resultado al programa principal.
    int num = receive();

    if(((num % 4 == 0) && (num % 100 != 0)) || (num % 400 == 0)) {
        send(pidPrincipal, 3);
    } else {
        send(pidPrincipal, 2);
    }
}

void proceso2(int pidPrincipal) {
    // Verifica si el número es primo y reporta el resultado al proceso principal.
    int num = receive();
    int esPrimo = 1;  // Supongo que es primo
    
    if (num <= 1) {
        esPrimo = 0;
    } else if (num > 2 && (num % 2 == 0)) {
        esPrimo = 0;      // Si es par, no es primo
    } else {
        int i = 3;
        while (esPrimo && (i * i <= num)) {
            // Verifico hasta la raiz cuadrada de numero
            if (num % i == 0) {
                esPrimo = 0;  // Si es divisible por i, entonces no es primo
            }
            i = i + 2;  // Solo evaluo los impares
        }
    }

    if(esPrimo) {
        send(pidPrincipal, 1);
    } else {
        send(pidPrincipal, 0);
    }
}
