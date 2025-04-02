#include "serial.h"

void uart_init(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void uart_putchar(char c)
{
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = c;
}

void uart_putstr(char *c, bool newline)
{

    int i = 0;
    while (1)
    {
        uart_putchar(c[i++]);
        if (c[i] == '\0')
            break;
    }

    if (newline)
        uart_newline();
}

void uart_putbuff(char *c, int len, bool newline)
{
    for (int i = 0; i < len; i++)
    {
        uart_putchar(c[i]);
    }

    if (newline)
        uart_newline();
}

char uart_getchar(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

void uart_newline(void)
{
    uart_putchar('\r');
    uart_putchar('\n');
}

int serial_monitor() {
    uart_init();

    char c;
    char buffer[256];
    int i = 0;

    while (1)
    {
        if (i >= 256) {
            uart_newline();
            uart_putstr("Buffer full! Exiting...", true);
            return -1;
        }

        c = uart_getchar();
        uart_putchar(c);
        buffer[i++] = c;

        if (c == '\x03') {
            i = 0;
            uart_newline();
        }

        if (c == '\n' || c == '\r') {
            buffer[i-1] = '\0';
            uart_newline();
            handle_commands(buffer);
            i = 0;
        }
    }

    return 0;
}

int handle_commands(char buffer[256]) {
    if (!strcmp(buffer, "help")) {
        uart_putstr("You made it to help!", true);
        return 0;
    }
    return -1;
}