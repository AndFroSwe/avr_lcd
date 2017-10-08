/* File: avr_lcd.c
 * Author: andfro
 * Description: Example program using library
 */

#include "avr_lcd.h"

int main(int argc, char *argv[])
{

    // Define output pins
    io_pin RS;
    RS.port = PORTB;
    RS.pin = PB0;

    // Set output pins
    DDRB |= _BV(PB0);

    // Enable pin
    enable_pin(RS);

    // Main loop
    while(1)
    

    return 0;
}
