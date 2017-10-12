/* File: avr_lcd.c
 * Author: andfro
 * Description: Example program using library
 */

#include "avr_lcd.h"

int main(int argc, char *argv[])
{
    // Define pins and a pin array
    const io_pin rs = {&PORTC, PC0};
    const io_pin rw = {&PORTC, PC1};
    const io_pin en = {&PORTC, PC2};
    const io_pin db4 = {&PORTD, PD0};
    const io_pin db5 = {&PORTD, PD1};
    const io_pin db6 = {&PORTD, PD2};
    const io_pin db7 = {&PORTD, PD3};
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
    DDRC = 0xFF;
    PORTC = 0x00;

    /* TEST */
    /*pin_on(lcd_on); // LCD off, (inverted logic)*/

    /*_delay_ms(1000);*/

    /* TEST */
    _delay_ms(1000); // Wait for everything to settle
    /*if(wait_busy()) init_lcd();*/
    /*wait_busy();*/
    // Set output pin
    /*pin_off(lcd_on); // LCD on, inverted logic*/

    /*pin_on(en);*/
    /*_delay_ms(10);*/
    /*pin_off(en);*/

    _delay_ms(1000);

    init_lcd(lcd);
    /*send_instr(0x28, lcd);*/
    /*send_instr(0x06, lcd);*/
    /*send_instr(0x0F, lcd);*/

    /*_delay_ms(1000);*/

    print_char('h', lcd);
    print_char('e', lcd);
    print_char('l', lcd);
    print_char('l', lcd);
    print_char('o', lcd);

    /*_delay_ms(1000);*/
    /*send_instr(0x01, lcd);*/

    /*print_char('w', lcd);*/
    /*print_char('o', lcd);*/
    /*print_char('r', lcd);*/
    /*print_char('l', lcd);*/
    /*print_char('d', lcd);*/
    /*print_char('!', lcd);*/

    /*send_instr(0x03, lcd);*/


    // Main loop
    while(1)
    {
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
        cli();
        _delay_ms(CMD_WAIT_TIME);
        pin_on(p.en);
        _delay_ms(CMD_WAIT_TIME);
        pin_off(p.en);
        _delay_ms(CMD_WAIT_TIME);
        sei();

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

    pin_on(p.rw);

    return 0;
}

int send_instr(int c, lcd_pins p)
{
    // Set to write to DR
    pin_off(p.rs);
    pin_off(p.rw);
    
    // Send command
    send_cmd(c, p);

    pin_on(p.rw);

    return 0;
}

int init_lcd(lcd_pins p)
{
    send_instr(0x28, p); // Function set
    _delay_ms(100);
    send_instr(0x06, p); // Entry mode
    _delay_ms(100);
    send_instr(0x01, p); // Clear display
    _delay_ms(150);
    send_instr(0x0F, p); // Cursor
    _delay_ms(10);
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
