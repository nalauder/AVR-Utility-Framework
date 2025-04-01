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
		DDRB &= ~((_BV(MOSI)) | (_BV(SCK)) | (_BV(SS))); /* Make COPI, SCK, SS as input pins */
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
	char flush_buffer;
	SPDR = data;					   /* Write data to SPI data register */
	loop_until_bit_is_set(SPSR, SPIF); /* Wait till transmission complete */
	flush_buffer = SPDR;			   /* Flush received data */
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