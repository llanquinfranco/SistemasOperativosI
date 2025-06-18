#include <xinu.h>
#define ASCII_ESC 27

void emisora(int emisora, int pidRadio, int retardo);
void radio_play(void);

int emisoraEmitiendo = 0;
const char * mensajes[] = {
" Mensaje de la primer radio \n",
" Segunda radio transmitiendo \n",
" Tercera emisora enviando \n",
};
sid32 semaforo;

void radio_control() {
    semaforo = semcreate(1);
    int pidRadio = create(radio_play, 2048, 20, "Radio play", 0);
    int pidEmisora1 = create(emisora, 2048, 20, "Emisora 1", 3, 1, pidRadio, 600);
    int pidEmisora2 = create(emisora, 2048, 20, "Emisora 2", 3, 2, pidRadio, 500);
    int pidEmisora3 = create(emisora, 2048, 20, "Emisora 3", 3, 3, pidRadio, 888);

    resume(pidRadio);
    resume(pidEmisora1);
    resume(pidEmisora2);
    resume(pidEmisora3);
    

    control(CONSOLE, TC_MODER, 0, 0);

    int salir = 0;
    printf("Comience a emitir\n");
    while(salir == 0) {
        char tecla = getchar();
        switch (tecla) {
            case 'q':   // Finaliza los procesos y reestablece la consola
                kill(pidEmisora1);
                kill(pidEmisora2);
                kill(pidEmisora3);
                kill(pidRadio);
                printf("\nFin de sintonia\n");
                control(CONSOLE, TC_MODEC, 0, 0);
                salir = 1;
                break;
            
            case '1':
                wait(semaforo);
                emisoraEmitiendo = 1;
                printf("\nRadio sintonizada 1\n");
                signal(semaforo);
                break;

            case '2':
                wait(semaforo);
                emisoraEmitiendo = 2;
                printf("\nRadio sintonizada 2\n");
                signal(semaforo);
                break;

            case '3':
                wait(semaforo);
                emisoraEmitiendo = 3;
                printf("\nRadio sintonizada 3\n");
                signal(semaforo);
                break;

            default:
            break;
        }
    }
}

void emisora(int emisora, int pidRadio, int retardo){
    int i = emisora - 1;
    int j = 0;
    char c;
    int n = emisora;
    int pidActual = getpid();
    while(1) {
        while(emisoraEmitiendo == emisora) {
            c = mensajes[i][j];
            if(c == ' ') {
                j = 0;
                c = mensajes[i][j];
            }
            int msg = (n << 8) | c;
            send(pidRadio, msg);
            j++;
            sleepms(retardo);
        }
    }
    
}

void radio_play(){
    while(1) {
        int msg = receive();
        int n = (msg >> 8);             // en la variable n quedó el nro de la emisora​
        char c = (char) (msg & 0xFF);   // en la variable c quedó la letra recibida del mensaje​
        wait(semaforo);
        printf("%c", c);                // Muestro la letra del mensaje
        signal(semaforo);
    }
}