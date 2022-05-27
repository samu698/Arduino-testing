#include <avr/boot.h>
#define F_CPU 16000000
#define BAUD 9600
#define URBB0_VAL (F_CPU / 8 / BAUD - 1)

#include "util.h"
#include "game.h"
#include "flash.h"
#include "spi.h"
#include "ssd1306.h"
#include "pins.h"

#include <avr/io.h>
#include <util/delay.h>

void blink_fast() {
	pinOn(D13);
	_delay_ms(100);
	pinOff(D13);
	_delay_ms(100);
}

void blink_slow() {
	pinOn(D13);
	_delay_ms(1000);
	pinOff(D13);
	_delay_ms(1000);
}

void setupSerial() {
	UBRR0 = URBB0_VAL; 		// set clock timing
	UCSR0A = 1 << U2X0; 	// set double clock speed
	UCSR0B = 1 << TXEN0;	// enable TX

	/*
	this is the default config so no need to set it
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //set 8 bit frames with 1 stop bit and no parity
	*/
}

void writeChar(uint8_t c) {
	while (!(UCSR0A & (1 << UDRIE0)));
	UDR0 = c;
}

void GCODE gameSetup() {
	setupSpi();
	setupSsd1306();
}
void GCODE gameUpdate(uint16_t dt) {
	invertPixel(0, 0);
	display();
	_delay_ms(1000);
}

void writeHexChar(uint8_t c) {
	char hi = c / 16;
	char low = c % 16;
	
	hi = hi < 10 ? hi + '0' : hi + 'A' - 10;
	low = low < 10 ? low + '0' : low + 'A' - 10;

	writeChar(hi);
	writeChar(low);
}

int main() {
	DDRB |= 1 << 5;

	_gameSetup();
	for (;;) _gameUpdate(0);
}
