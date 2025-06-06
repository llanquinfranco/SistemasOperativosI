#include <xinu.h>

sid32 sem;
pid32 owner;

// Funcion para inicializar el mutex
void mutex_init() {
    sem = semcreate(1);
    owner = -1;
}

// Funcion para adquirir el mutex
void mutex_lock() {
    wait(sem);
    owner = getpid();
}

// Funcion para liberar el mutex
void mutex_unlock() {
    if(owner == getpid()) { // Solo lo puede liberar el proceso que lo adquirio
        owner = -1;
        signal(sem);
    }
}