#define __AVR_ATmega328P__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BLINK_DELAY_MS 1000