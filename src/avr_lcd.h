/* File: avr_lcd.h
 * Author: andfro
 * Description: Header for example program using library
 */

// Defines
#define F_CPU 8000000UL

// Macros
#define PIN_ON(port, pin) port |= _BV(pin)
#define PIN_OFF(port, pin) port &= ~_BV(pin)
#define PIN_TOGGLE(port, pin) port ^= _BV(pin)


// Define pins
#define RS_PORT PORTB
#define RS_PIN PB0
#define EN_PORT PORTB
#define EN_PIN PB1

// Includes
#include <avr/io.h>
#include <util/delay.h>


