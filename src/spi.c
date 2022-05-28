#include "spi.h"
#include "pins.h"

// clockSetting = 0
// spcr = SPE | MSTR

void setupSpi() {
	uint8_t sregBak = SREG;
	cli();

	pinOutput(D10);
	pinOutput(PIN_MOSI);
	pinOutput(PIN_CLK);

	setBits(SPSR, bitMask(SPI2X)); // double clock speed

	// Set SPI mode as master
	// Enable SPI
	// Set clock divisor to 0
	// Set SPI_MODE0
	// Set MSB first
	SPCR = bitMask(MSTR) | bitMask(SPE);

	SREG = sregBak;
}

uint8_t spiTransfer(uint8_t data) {
	SPDR = data; // send the data in the SPI register
	nop();
	while (!readBit(SPSR, SPIF));
	return SPDR;
}
