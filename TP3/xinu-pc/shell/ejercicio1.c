#include <xinu.h>

void produce(void), consume(void);

int32 n = 0;    // Variable global compartida por todos los procesos
sid32 semProductor, semConsumidor;

// Problema productor-consumidor sin sincronizacion
void ejercicio1() {
    semProductor = semcreate(1);
    semConsumidor = semcreate(0);
    resume(create(consume, 1024, 20, "cons", 0));
    resume(create(produce, 1024, 20, "prod", 0));
}

// produce - incrementa n 2000 veces y termina
void produce() {
    int32 i;
    for(i = 1; i <= 2000; i++) {
        wait(semProductor);
        n++;
        signal(semConsumidor);
    }
}

// consume - imprime n 2000 veces y termina
void consume() {
    int32 i;
    for(i = 1; i <= 2000; i++) {
        wait(semConsumidor);
        printf("El valor de n es %d\n", n);
        signal(semProductor);
    }
}

/* Ejercicio 1b:

El programa no funciona como corresponde ya que no esta
sincronizado. Esto se debe a que el consumidor solo imprime
cuando el productor termina de incrementar 2000 veces

Para solucionar esto, se utilizan 2 semaforos, uno para 
avisarle al consumidor que imprima, y otro para avisarle
al productor que incremente

*/