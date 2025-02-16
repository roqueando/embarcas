#include <stdbool.h>
#include <io/io.hpp>
#include <spi/spi.hpp>

int main()
{
    shift_out_init();
    while (true)
    {
        send_to_lcd(0x80, true);
        send_to_lcd('H', false);
    }
    return 0;
}
