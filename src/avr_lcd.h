/* File: avr_lcd.h
 * Author: andfro
 * Description: Header for example program using library
 */

// Defines
#define F_CPU 8000000UL
#define CMD_WAIT_TIME 1

// LCD commands
#define CLR_SCREEN 0x01
#define FUNC_4BIT 0x28
#define AUTO_INC_NO_DISP_SH 0x06


// Macros
#define PIN_ON(port, pin) port |= _BV(pin)
#define PIN_OFF(port, pin) port &= ~_BV(pin)
#define PIN_TOGGLE(port, pin) port ^= _BV(pin)


// Define pins
#define RS_PORT PORTD
#define RS_PIN PD4
#define EN_PORT PORTD
#define EN_PIN PD5
#define RW_PORT PORTD
#define RW_PIN PD6
#define DB4_PORT PORTD
#define DB4_PIN PD0
#define DB5_PORT PORTD
#define DB5_PIN PD1
#define DB6_PORT PORTD
#define DB6_PIN PD2
#define DB7_PORT PORTD
#define DB7_PIN PD3

// Includes
#include <avr/io.h>
#include <util/delay.h>

// Typedefs
// Pin struct
typedef struct Io_pin {
    volatile uint8_t *port;
    int pin;
} io_pin;

typedef struct Lcd_pins {
    io_pin rs;
    io_pin rw;
    io_pin en;
    const io_pin *data;
} lcd_pins;

// Function prototypes
int send_cmd(int cmd, lcd_pins p);
int print_char(char c, lcd_pins p);
int send_instr(int i, lcd_pins p);
int init_lcd();
void pin_on(io_pin p);
void pin_off(io_pin p);
void pin_toggle(io_pin p);

