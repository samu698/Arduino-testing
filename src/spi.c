#include "spi.h"
#include <avr/io.h>

void setupSpi() {
	uint8_t sregBak = SREG;
	cli();

	DDRB |= (1 << DDB2) & (1 << DDB3) & ( 1 << DDB5);	// set SS, MOSI, SCK as outputs

	SPSR |= 1 << SPI2X;	// double clock speed

	///* these are unnecessary as they are the default values
	SPCR &= ~((1 << SPR1) & (1 << SPR0));	// set clock divisor
	SPCR &= ~((1 << CPOL) & (1 << CPHA));	// set SPI_MODE0
	SPCR &= ~(1 << DORD);	// set MSB FIRST
	//*/

	SPCR |= 1 << MSTR;	// set the SPI mode as master
	SPCR |= 1 << SPE;	// enable spi

	SREG = sregBak;
}

uint8_t spiTransfer(uint8_t data) {
	SPDR = data;	// send the data in the SPI register

	asm volatile ("nop");
	while (!(SPSR & (1 << SPIF)));

	return SPDR;
}
