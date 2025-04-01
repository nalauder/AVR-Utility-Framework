#include "main.h"

#define SS PORTB2
#define MOSI PORTB3
#define MISO PORTB4
#define SCK PORTB5

void spi_init(bool);
int spi_peripheral_run(void);