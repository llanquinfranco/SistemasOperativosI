#include <stdio.h>
#include <limits.h>

int main() {
    char a = CHAR_MAX;
    unsigned char b = UCHAR_MAX;

    printf("Valor maximo\n");
    printf("char: %d\n", a);
    printf("unsigned char: %u\n", b);

    a++;
    b++;

    printf("Despues de incrementar\n");
    printf("char: %d\n", a);
    printf("unsigned char: %u\n", b);

    return 0;
}