/* File: avr_lcd.h
 * Author: andfro
 * Description: Header for example program using library
 */

// Includes
#include <avr/io.h>

// Typedefs
typedef struct io_pin {
    int port;
    int pin;
} io_pin;

// Functions
int enable_pin(io_pin p)
{
    p.port |= _BV(p.pin);
}
