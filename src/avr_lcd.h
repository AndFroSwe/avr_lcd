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
#define RW_PORT PORTB
#define RW_PIN PB2
#define DB4_PORT PORTB
#define DB4_PIN PB3
#define DB5_PORT PORTB
#define DB5_PIN PB4
#define DB6_PORT PORTB
#define DB6_PIN PB5
#define DB7_PORT PORTB
#define DB7_PIN PB6

// Includes
#include <avr/io.h>
#include <util/delay.h>

// Function prototypes
int send_cmd(int cmd);
int print_char(int c);
int send_instr(int i);
