#define F_CPU 16000000

#include <avr/boot.h>
#include "util.h"
#include "game.h"
#include "flash.h"
#include "spi.h"
#include "ssd1306.h"
#include "pins.h"
#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

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

void GCODE gameSetup() {
	spiSetup();
	ssd1306Setup();
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

	serialWrite(hi);
	serialWrite(low);
}

int main() {
	pinOutput(D13);

	_gameSetup();
	for (;;) _gameUpdate(0);
}
