#include <stdio.h>
#include <limits.h>

int main() {
    char i;
    unsigned char j;
    printf("Rango de char: (%d; %d)\n", CHAR_MIN, CHAR_MAX);
    printf("Rango de unsigned char: (0; %u)\n", UCHAR_MAX);
    return 0;
}