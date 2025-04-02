/*low level api example for avr/arduino*/
#include "nrf24l01.h"

/*macros for SPI, CE and CSN pin configuration, change pins # according to mcu*/
#define MOSI_PIN    11
#define MISO_PIN    12
#define SCK_PIN     13
#define SS_PIN      10
#define NRF24_CSN   9             /*to enable SPI on nrf24, active LOW*/
#define NRF24_CE    8             /*active HIGH, activate chip in RX or TX mode*/

/*start of low level functions, specific to the mcu and compiler*/

/*delay in miliseconds*/
void delay_function(uint32_t duration_ms)
{
  _delay_ms(duration_ms);
  // delay
}

/*contains all SPI configuations, such as pins and control registers*/
/*SPI control: master, interrupts disabled, clock polarity low when idle, clock phase falling edge, clock up tp 1 MHz*/
void SPI_Initializer()
{
  // pinMode(MOSI_PIN, OUTPUT);
  // pinMode(MISO_PIN, INPUT);
  // pinMode(SCK_PIN, OUTPUT);
  // pinMode(SS_PIN, OUTPUT);
  DDRB |= ((_BV(MOSI)) | (_BV(SCK)) | (_BV(SS))); /* Mark COPI, SCK, SS as output pins */
  DDRB &= ~(_BV(MISO));							              /* Make CIPO pin as input pin */

  SPCR = 0X51;                      /*master, interrupt disabled, spi enabled, clock polarity low when idle, clock phase falling edge, 1 MHz clock*/
}

/*contains all CSN and CE pins gpio configurations, including setting them as gpio outputs and turning SPI off and CE '1'*/
void pinout_Initializer()
{
  // pinMode(NRF24_CSN, OUTPUT);
  // pinMode(NRF24_CE, OUTPUT);
  DDRB |= ((_BV(CSN)) | (_BV(CE)));     /* Set CSN and CE as outputs */

  // digitalWrite(NRF24_CSN, SPI_OFF);       /*nrf24l01 is not accepting commands*/
  PORTB |= _BV(CSN);

  nrf24_CE(1);                         /*no need to change this line*/

}

/*CSN pin manipulation to high or low (SPI on or off)*/
void nrf24_SPI(uint8_t input)
{
  if (input == SPI_ON)
    // digitalWrite(NRF24_CSN, LOW);
    PORTB &= ~(_BV(CSN));
  else
    // digitalWrite(NRF24_CSN, HIGH);
    PORTB |= _BV(CSN);
}

/*1 byte SPI shift register send and receive routine*/
uint8_t SPI_send_command(uint8_t command)
{
  SPDR = command;
  while ((SPSR & (1 << SPIF)) == 0) {}
  return SPDR;
}

/*CE pin maniplation to high or low*/
void nrf24_CE(uint8_t input)
{
  if (input == CE_ON)
    // digitalWrite(NRF24_CE, HIGH);
    PORTB |= _BV(CE);
  else
    // digitalWrite(NRF24_CE, LOW);
    PORTB &= ~(_BV(CE));
}
