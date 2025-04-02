
#ifndef SERIAL_H_
#define SERIAL_H_

#include "main.h"

#define BAUD 9600

#include <util/setbaud.h>
#include <string.h>

void uart_init(void);
void uart_putchar(char c);
char uart_getchar(void);
void uart_putstr(char* c, bool newline);
void uart_putbuff(char* c, int len, bool newline);
void uart_newline(void);
int serial_monitor(void);
int handle_commands(char buffer[256]);

#endif