#include "spi.h"

char buffer[256];
bool process;

void spi_init(bool controller)
{
	if (controller)
	{
		DDRB |= ((_BV(MOSI)) | (_BV(SCK)) | (_BV(SS))); /* Mark COPI, SCK, SS as output pins */
		DDRB &= ~(_BV(MISO));							/* Make CIPO pin as input pin */
		SPCR |= (_BV(MSTR));							/* Put SPI in master mode */
		SPCR |= _BV(SPE);								/* Enable SPI*/
	}
	else
	{
		DDRB &= ~((_BV(MOSI)) | (_BV(SCK)) | (_BV(SS))); /* Mark COPI, SCK, SS as input pins */
		DDRB |= (_BV(MISO));							 /* Make CIPO pin as output pin */
		SPCR &= ~(_BV(MSTR));							 /* Enable SPI in slave mode */
		SPCR |= _BV(SPE);								 /* Enable SPI*/
	}
	SPDR;
}

char SPI_Receive() /* SPI Receive data function */
{
	loop_until_bit_is_set(SPSR, SPIF); /* Wait till reception complete */
	return SPDR;					   /* Return received data */
}

void SPI_Write(char data) /* SPI write data function */
{
	// char _flush_buffer;
	SPDR = data;					   /* Write data to SPI data register */
	loop_until_bit_is_set(SPSR, SPIF); /* Wait till transmission complete */
	(SPDR);			   /* Flush received data */
									   /* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}

char SPI_Transfer(char data) /* SPI Transfer data function */
{
	SPDR = data;					   /* Write data to SPI data register */
	loop_until_bit_is_set(SPSR, SPIF); /* Wait till transmission complete */
	return SPDR;					   /* Flush received data */
}

int spi_peripheral_run(void)
{
	int i = 0;
	bool recv = true;
	while (1)
	{
		if (recv)
			buffer[i] = SPI_Transfer(0);
		else
			SPI_Transfer(buffer[i]);

		if (buffer[i++] == '\0')
		{
			recv = !recv;
			i = 0;
		}
		else if (i >= 256)
		{
			SPI_Write('\0');
			i = 0;
		}
	}
	return 0;
}

char SPI_Controller_Transfer(char data)
{
	PORTB &= ~(_BV(1 << SS));
	_delay_ms(1);
	char recv = SPI_Transfer(data);
	_delay_ms(1);
	PORTB |= _BV(1 << SS);
	return recv;
}

int spi_controller_run(void)
{
	int i = 0;
	char *p;
	while (1)
	{
		p = "God damn finally!!!";
		do
			SPI_Controller_Transfer(*p);
		while (*p++);

		do
		{
			buffer[i] = SPI_Controller_Transfer(0);
			if (i >= 256)
				break;
		} while (buffer[i++] != '\0');

		i = 0;
		uart_putstr(buffer, true);
		_delay_ms(1000);
	}
	return 0;
}