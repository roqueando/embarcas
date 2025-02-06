#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


int main()
{
    char value = 0;
    if (value & 0x80) {
        printf("value: %b\n", value);
    }
    printf("value: %b\n", value);
}
