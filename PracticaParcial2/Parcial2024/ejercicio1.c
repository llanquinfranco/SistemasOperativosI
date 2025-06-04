#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>      // open(), constantes O_
#include <unistd.h>     // read(), close()

#define TAMANIO 1000
#define ARCHIVO "desordenado.txt"

int arreglo[TAMANIO];
int arregloFusionado[TAMANIO];


// Estructura para pasar argumentos a los hilos
typedef struct {
    int inicio;
    int fin;
} structArgumentos;

// Metodo de ordenamiento burbuja
void ordenar(int inicio, int fin) {
    int i, j, aux;
    for(i = inicio; i < fin - 1; i++) {
        for(j = inicio; j < fin - 1 - (i - inicio); j++) {
            if(arreglo[j] > arreglo[j + 1]) {
                aux = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = aux;
            }
        }
    }
}

// Función que ejecuta cada hilo
void* ejecutar(void* arg) {
    structArgumentos* datos = (structArgumentos*)arg;
    ordenar(datos->inicio, datos->fin);
    return NULL;
}

void fusionar() {
    int i = 0;              // Indice para la 1ra mitad (0 a 499)
    int j = TAMANIO / 2;    // Indice para la 2da mitad (500 a 999)
    int k = 0;              // Indice para el arreglo fusionado

    while(i < TAMANIO / 2 && j < TAMANIO) { // Mientras no se termine ninguna de las mitades
        if(arreglo[i] < arreglo[j]) {   // Copio el menor de los dos
            arregloFusionado[k] = arreglo[i];
            i++;    // Avanzo en la 1ra mitad
        } else {
            arregloFusionado[k] = arreglo[j];
            j++;    // Avanzo en la 2da mitad
        }
        k++;    // Avanzo en 'arregloFusionado'
    }

    // Si todavia quedan elementos en la 1ra mitad
    while(i < TAMANIO / 2) {
        arregloFusionado[k] = arreglo[i];
        i++;
        k++;
    }

    // Si todavia quedan elementos en la 2da mitad
    while(j < TAMANIO) {
        arregloFusionado[k] = arreglo[j];
        j++;
        k++;
    }
}

int main() {

    pthread_t hilo1, hilo2;
    structArgumentos argumentos[2];
    
    // Abrir archivo binario
    int fd = open(ARCHIVO, O_RDONLY);
    if(fd == -1) {
        printf("Error abriendo el archivo\n");
        return -1;
    }

    // Leer los enteros y colocarlos en 'arreglo'
    read(fd, arreglo, TAMANIO * sizeof(int));
    close(fd);

    // Configurar rangos para cada hilo
    int mitad = TAMANIO / 2;
    argumentos[0].inicio = 0;
    argumentos[0].fin = mitad;
    argumentos[1].inicio = mitad;
    argumentos[1].fin = TAMANIO;

    // Crear threads independientes, cada uno de los cuales ejecutara una funcion
    pthread_create(&hilo1, NULL, ejecutar, &argumentos[0]);
    pthread_create(&hilo2, NULL, ejecutar, &argumentos[1]);

    // Espera a que los hilos completen su tarea antes de continuar
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    fusionar();

    // Mostrar el arreglo fusionado ordenado
    printf("Arreglo fusionado \n");
    for(int i = 0; i < TAMANIO; i++) {
        printf("%d\n", arregloFusionado[i]);
    }

    return 0;
}