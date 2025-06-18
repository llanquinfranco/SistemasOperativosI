/* kbdgetc.c  -  kbdgetc */

#include <xinu.h>
#include <keyboard.h>

/*------------------------------------------------------------------------
 * kbdgetc  -  Lee un byte del buffer de manera sincronizada 
 *------------------------------------------------------------------------
 */

unsigned char kbdgetc() {
    if(getpid() != pidTeclado) {
        return SYSERR;
    }
    wait(buffer.semEspacio);
    
    unsigned char c = buffer.entradas[buffer.indiceInicio];
    buffer.entradas[buffer.indiceInicio] = 0;
    buffer.indiceInicio = (buffer.indiceInicio + 1) % SIZE;

    return c;
}

