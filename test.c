#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#define bittst(arg, bit) (arg & (1<<bit))


int main()
{
    char value = 0x3F; // 0b0011 1111
                       // 0b1000 0000
                       // ------&-----
                       // 0b0000 0000 (false)
                       // ----<<=1----
                       // 0b0111 1110
                       // 0b1000 0000
                       // ------&-----
                       // 0b0000 0000 (false)
                       // ----<<=1----
                       // 0b1111 1100
                       // 0b1000 0000
                       // ------&-----
                       // 0b1000 0000 (true)
    printf("0b");
    for (int i = 0; i < 8; i++) {
        if (value & 0x01) {
            printf("1");
        } else {
            printf("0");
        }
        value >>= 1;
    }
    printf("\n");
    printf("value: %b\n", value);
    return 0;
}
