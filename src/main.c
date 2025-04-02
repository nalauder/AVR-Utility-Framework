#include "main.h"

int main(void)
{
    uart_init();
    spi_init(true);
    return spi_controller_run();
    // return serial_monitor();
}

void blink_delay(void)
{
    /* Using the DDRB register, configure port 5 to be an output */
    DDRB |= (_BV(PORTB5));

    while (1)
    {
        /* Write 1 to the PINB register for port 5, this toggles on and off even through it writes 1 each time */
        PINB |= (_BV(PORTB5));
        _delay_ms(BLINK_DELAY_MS);
    }
}