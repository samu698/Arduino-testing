#include "serial.h"
#include <avr/io.h>

#define URBB0_VAL (F_CPU / 8 / BAUD - 1)

void serialSetup() {
	UBRR0 = URBB0_VAL; // Set clock timing
	setBits(UCSR0A, bitMask(U2X0)); // Set double clock speed
	setBits(UCSR0B, bitMask(TXEN0)); // Enable TX

	setBits(UCSR0C, bitMask(UCSZ00) | bitMask(UCSZ01)); // Set 8 bit frames with 1 stop bit and no parity
}

void serialWrite(uint8_t byte) {
	nop(); // A small wait to prevent the while looping
	while (!readBit(UCSR0A, UDRIE0));
	UDR0 = byte;
}

void serialWriteBuffer(uint8_t* data, uint16_t length) {
	for (uint16_t i = 0; i < length; i++) {
		nop(); // A small wait to prevent the while looping
		while (!readBit(UCSR0A, UDRIE0));
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
