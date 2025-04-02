#ifndef NRF24_H_
#define NRF24_H_

#include "main.h"
#include "nrf24l01.h"

#define CE PORTB0
#define CSN PORTB1
// #define CE_PIN 7
// #define CSN_PIN 8


void radio_init(void);
int radio_run(bool);


#endif