# Makefile for avr_lcd project

# Parameters
CC = avr-gcc
MMCU = atmega328p
PROGRAMMER = atmelice_isp
OBJCOPY = avr-objcopy

# Main file name
MAIN = avr_lcd

all: obj/avr_lcd.elf build/avr_lcd.hex

# Create hex file
build/avr_lcd.hex: obj/avr_lcd.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

# Compile elf files
obj/avr_lcd.elf: obj/avr_lcd.o
	$(CC) -mmcu=$(MMCU) -o $@ $< 

# Compile object files
obj/avr_lcd.o: src/avr_lcd.c
	$(CC) -mmcu=$(MMCU) -c -o $@ $< 

# Utility functions
clean:
	rm obj/*.elf obj/*.o build/*.hex -f
