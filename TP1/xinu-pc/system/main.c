/*  main.c  - main */

#include <xinu.h>


extern paint_screen();
extern print_text_on_vga(unsigned int x, unsigned int y, const char * t);
extern void sndA(void);	// Como estan en otro archivo, los pongo como extern
extern void sndB(void);	// Lo mismo

process	main(void)
{

	paint_screen();
	print_text_on_vga(10, 200, "Xinu OS for PC with VGA support");
	print_text_on_vga(10, 220, "Sistemas Operativos I");
	print_text_on_vga(10, 240, "Franco Llanquin");

	//recvclr();

	// Creo los procesos de ejercicio4.c
	pid32 proceso1 = create(sndA, 1024, 20, "process 1", 0);
    pid32 proceso2 = create(sndB, 1024, 20, "process 2", 0);

	// Inicio los procesos (es como un start() ¿?)
	resume(proceso1);
    resume(proceso2);

	// Espera de 10 segundos
	sleep(10);

	// Finalizo los 2 procesos
	kill(proceso1);
	kill(proceso2);

	recvclr();

	// Luego inicia la shell de siempre
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	
	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
