#include <stdbool.h>
#include <io/io.hpp>
#include <servo/servo.hpp>

int main()
{
    servo_init();
    while (true)
    {
        turn_clockwise();
        turn_counter_clockwise();
    }
    return 0;
}
