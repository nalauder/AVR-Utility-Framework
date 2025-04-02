#ifndef MAIN_H_
#define MAIN_H_

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdbool.h>

#include "serial.h"
#include "spi.h"
#include "radio.h"

#define BLINK_DELAY_MS 1000

#endif