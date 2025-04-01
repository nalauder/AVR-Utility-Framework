To compile and program board:
> avr-gcc main.c
> avr-objcopy -O ihex -R .eeprom a.out a.hex
> avrdude -c usbasp-clone -p m328p -F -U flash:w:./a.hex:i