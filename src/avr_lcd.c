/* File: avr_lcd.c
 * Author: andfro
 * Description: Example program using library
 */

#include "avr_lcd.h"

int main(int argc, char *argv[])
{
    DDRB |= _BV(PB0);

    // Main loop
    while(1)
    {
        PIN_TOGGLE(RS_PORT, RS_PIN);
        _delay_ms(500);
    }
    

    return 0;
}
