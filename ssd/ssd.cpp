#include "ssd.h"
#include "../io/io.h"
#include "../shift_register/shift_register.h"

#define DISP1_PIN {mode::OUTPUT, 0, available_port::C}
#define DISP2_PIN {mode::OUTPUT, 1, available_port::C}
#define DISP3_PIN {mode::OUTPUT, 2, available_port::C}
#define DISP4_PIN {mode::OUTPUT, 3, available_port::C}

static const char values[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F,
    0x77, 0x7C, 0x39,0x5E, 0x79,
    0x71
};

static char display;
static char v0=0, v1=0, v2=0, v3=0;

void ssd_init()
{
    so_init();

    // PORTC will select the display
    for (uint8_t ix = 0; ix < 4; ix++) {
        set_port_direction({mode::OUTPUT, ix, available_port::C});
    }

    // will be the shift register PORT
    set_port_direction({mode::OUTPUT, 0, available_port::D});
    set_port_direction({mode::OUTPUT, 1, available_port::D});
    set_port_direction({mode::OUTPUT, 2, available_port::D});
}

void ssd_digit(int position, char value)
{
    if (position == 0) { v0 = value; }
    if (position == 1) { v1 = value; }
    if (position == 2) { v2 = value; }
    if (position == 3) { v3 = value; }
}

void ssd_update()
{
    digital_write(DISP1_PIN, pin_state::LOW);
    digital_write(DISP2_PIN, pin_state::LOW);
    digital_write(DISP3_PIN, pin_state::LOW);
    digital_write(DISP4_PIN, pin_state::LOW);

    switch (display) {
        case 0:
            so_write(values[v0]);
            digital_write(DISP1_PIN, pin_state::HIGH);
            display = 1; break;
        case 1:
            so_write(values[v1]);
            digital_write(DISP2_PIN, pin_state::HIGH);
            display = 2; break;
        case 2:
            so_write(values[v2]);
            digital_write(DISP3_PIN, pin_state::HIGH);
            display = 3; break;
        case 3:
            so_write(values[v3]);
            digital_write(DISP4_PIN, pin_state::HIGH);
            display = 0; break;
        default:
            display = 0;
            break;
    }
}
