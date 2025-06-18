/* Son alias para funciones inb y outb que se utilizan para
realizar operaciones de E/S en puertos especificos*/
#define inportb(p)      inb(p)
#define outportb(p,v)   outb(p,v)

/* Registro de datos del teclado. Se utiliza para leer 
pulsaciones de teclas y para escribir datos hacia el teclado */
#define KEYBOARD_DATAREG 0x60  // :Data Register(Read\Write)

/* Registro de comandos del teclado. Se utiliza
para enviar comandos al controlador del teclado */
#define KEYBOARD_CMDREG 0x64   // :Command Register(Read\Write)

// Tamaño del buffer (10 entradas)
#define SIZE 10

extern unsigned char kblayout [128];  // { ... } Fill your layout yourself 

typedef struct {
    unsigned char entradas[SIZE];
    int32 indiceInicio;
    int32 indiceFinal;
    sid32 semEspacio;
} Buffer;

extern Buffer buffer;              // nombre de la instancia, que usarás en todos los .c
extern pid32 pidTeclado;
extern sid32 semaforoTeclado;