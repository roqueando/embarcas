#include <stdbool.h>
#include <io/io.h>

int main()
{
    BIT_SET(DDRB, DDB2);
    while (true) {
        PORTB |= (1 << PB2);
        // timer here
        PORTB &= ~(1 << PB2);
    }
    return 0;
}
