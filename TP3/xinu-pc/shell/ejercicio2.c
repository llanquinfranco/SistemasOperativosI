#include <xinu.h>
#include <mutex.h>

void operar(void), incrementar(void);

unsigned char x = 0;

// ejercicio2 - programa con regiones criticas
void ejercicio2() {
    mutex_init();
    resume(create(operar, 1024, 20, "process 1", 0));
    resume(create(incrementar, 1024, 20, "process 2", 0));
    sleep(10);
}

// operar x e y
void operar() {
    int y = 0;
    printf("Si no existen mensajes de ERROR entonces todo va OK!\n");
    while(1) {
        mutex_lock();
        /* si x es multiplo de 10 */
        if((x % 10) == 0) {
            y = x * 2; /* como y es el doble de x entonces y es multiplo de 10 tambien */
            /* si y no es multiplo de 10 entonces hubo un error */
            if((y % 10) != 0) {
                printf("\r ERROR!! y=%d, x=%d \r", y, x);
            }
        }
        mutex_unlock();
    }
}

// incrementar x
void incrementar() {
    while(1) {
        mutex_lock();
        x = x + 1;
        mutex_unlock();
    }
}