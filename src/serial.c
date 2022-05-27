#include "serial.h"
#include <avr/io.h>

#define URBB0_VAL (F_CPU / 8 / BAUD - 1)

void setupSerial() {
	UBRR0 = URBB0_VAL; 		// set clock timing
	UCSR0A = 1 << U2X0; 	// set double clock speed
	UCSR0B = 1 << TXEN0;	// enable TX

	/*
	this is the default config so no need to set it
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //set 8 bit frames with 1 stop bit and no parity
	*/
}

void serialWrite(uint8_t byte) {
	nop(); // just a small wait to prevent the while looping
	while (!(UCSR0A & (1 << UDRIE0)));
	UDR0 = byte;
}

void serialWriteBuffer(uint8_t* data, uint16_t length) {
	for (uint16_t i = 0; i < length; i++) {
		nop(); // just a small wait to prevent the while looping
		while (!(UCSR0A & (1 << UDRIE0)));
		UDR0 = data[i];
	}
}

void serialPrintUNum(uint64_t unsingedNum) {
	uint8_t digitsBuffer[sizeof unsingedNum * 8];
	uint8_t pos = sizeof digitsBuffer - 1;

	do {
		digitsBuffer[pos--] = unsingedNum % 10 + '0';
		unsingedNum /= 10;
	} while (unsingedNum != 0);

	serialWriteBuffer(digitsBuffer + pos, sizeof digitsBuffer - pos);
}

void serialPrintSNum(int64_t signedNumber) {
	// TODO
}
