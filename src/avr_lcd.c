/* File: avr_lcd.c
 * Author: andfro
 * Description: Example program using library
 */

#include "avr_lcd.h"

int main(int argc, char *argv[])
{
    // Define pins and a pin array
    const io_pin rs = {&PORTD, PD0};
    const io_pin rw = {&PORTD, PD1};
    const io_pin en = {&PORTD, PD2};
    const io_pin db4 = {&PORTD, PD3};
    const io_pin db5 = {&PORTD, PD4};
    const io_pin db6 = {&PORTD, PD5};
    const io_pin db7 = {&PORTD, PD6};
    const io_pin data[]  = {db4, db5, db6, db7};

    // Collect them into struct
    const lcd_pins lcd = {
        rs,
        rw,
        en,
        data
    };


    DDRD = 0xFF;
    PORTD = 0x00;
    _delay_ms(2000); // Wait for everything to settle
    /*if(wait_busy()) init_lcd();*/
    /*wait_busy();*/
    // Set output pin
    
    init_lcd(lcd);

    /*_delay_ms(1000);*/

    /*print_char('h');*/
    /*print_char('e');*/
    /*print_char('l');*/
    /*print_char('l');*/
    /*print_char('o');*/

    // Main loop
    while(1)
    {
        _delay_ms(1000);
    }
    

    return 0;
}

int send_cmd(int cmd, lcd_pins p)
{
    // Send first MS bits, then LS
    char nibble = 0x0;
    int i = 1;
    while (i >= 0)
    {
        nibble = (cmd >> 4*i) & 0x0F; // Shift cmd into nibble

        // Enable correct pins
        int j = 0;
        for (j = 0; j < 4; ++j) {
            if ((nibble >> j) & 0x01) {
                pin_on(p.data[j]);
            } else {
                pin_off(p.data[j]);
            }
        }

        // Send command
        _delay_ms(CMD_WAIT_TIME);
        pin_on(p.en);
        _delay_ms(CMD_WAIT_TIME);
        pin_off(p.en);
        _delay_ms(CMD_WAIT_TIME);

        // Decrement i
        --i;
    }

    return 0;
}

int print_char(char c, lcd_pins p)
{
    // Set to write to DR
    pin_on(p.rs);
    pin_off(p.rw);
    
    // Send command
    send_cmd(c, p);

    return 0;
}

int send_instr(int c, lcd_pins p)
{
    // Set to write to DR
    pin_on(p.rs);
    pin_off(p.rw);
    
    // Send command
    send_cmd(c, p);

    return 0;
}

int init_lcd(lcd_pins p)
{
    send_instr(0x28, p); // Function set
    _delay_ms(1);
    send_instr(0x06, p); // Entry mode
    _delay_ms(1);
    /*send_instr(0x01, p); // Clear display*/
    _delay_ms(15);
    send_instr(0x0F, p); // Cursor
    _delay_ms(1);
    /*send_instr(0x03); // Return home*/

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
