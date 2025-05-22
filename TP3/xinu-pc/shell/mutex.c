#include <xinu.h>

sid32 sem;
pid32 owner;

void mutex_init() {
    sem = semcreate(1);
    owner = -1;
}

void mutex_lock() {
    wait(sem);
    owner = getpid();
}

void mutex_unlock() {
    if(owner == getpid()) {
        owner = -1;
        signal(sem);
    }
}