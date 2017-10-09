/* File: avr_lcd.c
 * Author: andfro
 * Description: Example program using library
 */

#include "avr_lcd.h"

int main(int argc, char *argv[])
{
    const io_pin pd0 = {&PORTD, PD0};

    DDRD = 0xFF;
    PORTD = 0x00;
    _delay_ms(2000); // Wait for everything to settle
    /*if(wait_busy()) init_lcd();*/
    /*wait_busy();*/
    // Set output pin
    
    /*init_lcd();*/

    /*_delay_ms(1000);*/

    /*print_char('h');*/
    /*print_char('e');*/
    /*print_char('l');*/
    /*print_char('l');*/
    /*print_char('o');*/

    // Main loop
    while(1)
    {
        pin_toggle(pd0);
        _delay_ms(1000);
    }
    

    return 0;
}

int send_cmd(int cmd)
{
    // Send first MS bits, then LS
    int nibble = 0x00;
    int i = 0;
    for (i = 1;  i >= 0; --i) {
        nibble = cmd >> 4*i;
        // Enable pins
        if (nibble & 0x01) {
            PIN_ON(DB4_PORT, DB4_PIN);
        } else {
            PIN_OFF(DB4_PORT, DB4_PIN);
        }
        if ((nibble >> 1) & 0x01) {
            PIN_ON(DB5_PORT, DB5_PIN);
        } else {
            PIN_OFF(DB5_PORT, DB5_PIN);
        }
        if ((nibble >> 2) & 0x01) {
            PIN_ON(DB6_PORT, DB6_PIN);
        } else {
            PIN_OFF(DB6_PORT, DB6_PIN);
        }
        if ((nibble >> 3) & 0x01) {
            PIN_ON(DB7_PORT, DB7_PIN);
        } else {
            PIN_OFF(DB7_PORT, DB7_PIN);
        }

        // Send message
        PIN_ON(EN_PORT, EN_PIN);
        _delay_ms(CMD_WAIT_TIME);
        PIN_OFF(EN_PORT, EN_PIN);
        _delay_ms(CMD_WAIT_TIME);
    }

    return 0;
}

int print_char(char c)
{
    // Set to write to DR
    PIN_ON(RS_PORT, RS_PIN);
    PIN_OFF(RW_PORT, RW_PIN);
    
    // Send command
    send_cmd(c);

    return 0;
}

int send_instr(int i)
{
    // Set to write to DR
    PIN_OFF(RS_PORT, RS_PIN);
    PIN_OFF(RW_PORT, RW_PIN);

    // Send command
    send_cmd(i);

    return 0;
}

int init_lcd()
{
    send_instr(0x28); // Function set
    _delay_ms(1);
    send_instr(0x06); // Entry mode
    _delay_ms(1);
    /*send_instr(0x01); // Clear display*/
    _delay_ms(15);
    send_instr(0x0F); // Cursor
    _delay_ms(1);
    /*send_instr(0x03); // Return home*/

    return 0;
}

int wait_busy()
{
    // Does not work
    // Enable read
    PIN_OFF(RS_PORT, RS_PIN);
    PIN_ON(RW_PORT, RW_PIN);

    // Read busy flag until lcd is ready
    DDRD &= ~_BV(DB7_PIN); // Set DB 7 to input
    PORTD |= _BV(DB7_PIN); // Enable pullup
    int i = 1;
    while(i) {
        PIN_ON(EN_PORT, EN_PIN);
        _delay_ms(1);
        i = (PIND >> DB7_PIN) & 0x01;
        PIN_OFF(EN_PORT, EN_PIN);
        } // Poll flag
    DDRD |= _BV(DB7_PIN); // Set to output again

    // Set back to write mode
    PIN_ON(RS_PORT, RS_PIN);

    return 0;
}

void pin_on(io_pin p)
{
    *p.port |= _BV(p.pin);
}

void pin_off(io_pin p)
{
    *p.port &= ~_BV(p.pin);
}

void pin_toggle(io_pin p)
{
    *p.port ^= _BV(p.pin);
}
