#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


int main()
{
    char led = 6;
    if (led & 4) {
        printf("led: %b\n", led);
    }
    printf("led: %b\n", led);
}
