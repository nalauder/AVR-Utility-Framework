#ifndef SPI_H_
#define SPI_H_

#include "main.h"
#include "serial.h"

#define SS PORTB2
#define MOSI PORTB3
#define MISO PORTB4
#define SCK PORTB5

void spi_init(bool);
int spi_peripheral_run(void);
int spi_controller_run(void);
char SPI_Transfer(char);

#endif