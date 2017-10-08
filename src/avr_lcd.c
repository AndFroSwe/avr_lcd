/* File: avr_lcd.c
 * Author: andfro
 * Description: Example program using library
 */

#include "avr_lcd.h"

int main(int argc, char *argv[])
{
    DDRD = 0xFF;
    PORTD = 0x00;
    _delay_ms(2000); // Wait for everything to settle
    // Set output pin

    init_lcd();

    print_char('h');
    print_char('e');
    print_char('l');
    print_char('l');
    print_char('o');

    // Main loop
    while(1)
    {
    }
    

    return 0;
}

int send_cmd(int cmd)
{
    // Send first MS bits, then LS
    int nibble;
    int i;
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
        _delay_ms(WAIT_TIME);
        PIN_OFF(EN_PORT, EN_PIN);
        _delay_ms(WAIT_TIME);
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
    send_instr(0x28);
    send_instr(0x06);
    send_instr(0x0F);
    send_instr(0x01);
}
