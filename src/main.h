#ifndef MAIN_H_
#define MAIN_H_

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "serial.h"
#include "spi.h"

#define BLINK_DELAY_MS 1000

#endif