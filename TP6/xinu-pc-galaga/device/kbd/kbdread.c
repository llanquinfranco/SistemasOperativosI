/* kbdread.c  -  kbdread */

#include <xinu.h>
#include <mouse.h>

/*------------------------------------------------------------------------
 * kbdread  -  Read the status of the keyboard driver
 *------------------------------------------------------------------------
 */
devcall	kbdread (
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char          *buffer,        /* Address of buffer            */
          uint32        count           /* Length of buffer             */
	)
{
	// Implementar únicamente la solicitud de un byte, para simplificar
    buffer[0] = kbdgetc();
	return 1;
}
