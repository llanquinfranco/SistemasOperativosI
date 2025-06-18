/* kbdclose.c  -  kbdclose */

#include <xinu.h>
#include <keyboard.h>

/*------------------------------------------------------------------------
 * kbdclose  -  Close the keyboard device
 *------------------------------------------------------------------------
 */
devcall	kbdclose (
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	if(getpid() != pidTeclado) {
		// Solo el proceso que abrió puede cerrar
		return SYSERR;
	}
	pidTeclado = -1;			// Reseteo el PID
	signal(semaforoTeclado);	// Libero el semaforo para que otro proceso pueda acceder al teclado
}
