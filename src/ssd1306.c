#include "ssd1306.h"
#include "spi.h"
#include <avr/io.h>

#define COMMAND_MODE() pinOff(SSD1306_DC)
#define DATA_MODE() pinOn(SSD1306_DC)
#define SELECT() pinOff(SSD1306_CS)
#define DESELECT() pinOff(SSD1306_CS)

#define DISPLAY_OFF 0xAE
#define SET_CLK_DIV 0xD5
#define SET_MULTIPLEX 0xA8
#define SET_DISPLAY_OFFSET 0xD3
#define SET_START_START_LINE 0x40
#define SET_PUMP_SETTING 0x8D
#define SET_MEM_ACCESS_MODE 0x20
#define SET_SEGMENT_REMAP 0xA0
#define SET_COM_OUT_SCAN_DIR 0xC0
#define SET_COM_PINS_CONFIG 0xDA
#define SET_CONTRAST 0x81
#define SET_PRE_CHARGE 0xD9
#define SET_VCOMH_DESEL_LVL 0xDB
#define DISPLAY_RAM_RSM 0xA4
#define SET_DISPLAY_MODE 0xA6
#define DEACTIVATE_SCROLL 0x2E
#define DISPLAY_ON 0xAF

#define SET_PAGE_ADDRESS 0x22
#define SET_COLUMN_ADDRESS 0x21

uint8_t displayBuffer[(DWIDTH * (DHEIGHT + 7)) / 8] = { 0 };

void ssd1306Setup() {
	pinOutput(SSD1306_DC);
	pinOutput(SSD1306_CS);

	uint8_t sregBak = SREG;
	cli();
	SELECT();

	COMMAND_MODE();
	spiTransfer(DISPLAY_OFF); //default

	spiTransfer(SET_CLK_DIV); //default
	spiTransfer(0x80);

	spiTransfer(SET_MULTIPLEX);
	spiTransfer(DHEIGHT - 1);

	spiTransfer(SET_DISPLAY_OFFSET); // default
	spiTransfer(0x00);

	spiTransfer(SET_START_START_LINE | 0x00); // default

	spiTransfer(SET_PUMP_SETTING);
	spiTransfer(0x14);	// enable

	spiTransfer(SET_MEM_ACCESS_MODE);
	spiTransfer(0x00); // horizzontal access

	spiTransfer(SET_SEGMENT_REMAP | 0x01); // enable
	
	spiTransfer(SET_COM_OUT_SCAN_DIR | 0x08); // remapped mode

	spiTransfer(SET_COM_PINS_CONFIG); // default
	spiTransfer(0x12);

	spiTransfer(SET_CONTRAST);
	spiTransfer(0xCF);

	spiTransfer(SET_PRE_CHARGE);
	spiTransfer(0xF1);

	spiTransfer(SET_VCOMH_DESEL_LVL);
	spiTransfer(0x40);

	spiTransfer(DISPLAY_RAM_RSM | 0x00);

	spiTransfer(SET_DISPLAY_MODE | 0x00); // default

	spiTransfer(DEACTIVATE_SCROLL);

	spiTransfer(DISPLAY_ON);
	
	DESELECT();
	SREG = sregBak;
}

void setPixel(uint8_t x, uint8_t y) {
	// FIXME: handle rotation
	displayBuffer[x + (y / 8) * DWIDTH] |= 1 << (y % 8);
}
void clearPixel(uint8_t x, uint8_t y) {
	// FIXME: handle rotation
	displayBuffer[x + (y / 8) * DWIDTH] &= ~(1 << (y % 8));
}
void invertPixel(uint8_t x, uint8_t y) {
	// FIXME: handle rotation
	displayBuffer[x + (y / 8) * DWIDTH] ^= 1 << (y % 8);
}
void clearDisplay() {
	utilMemset(displayBuffer, 0, sizeof displayBuffer);
}

void display() {
	uint8_t sregBak = SREG;
	cli();
	SELECT();

	COMMAND_MODE();
	spiTransfer(SET_PAGE_ADDRESS);
	spiTransfer(0x00);	// page begin
	spiTransfer(0xFF);	// page end (should it be 0x7F?)

	spiTransfer(SET_COLUMN_ADDRESS);
	spiTransfer(0x00);
	spiTransfer(DWIDTH - 1);

	DATA_MODE();
	for (uint16_t i = 0; i < sizeof displayBuffer; i++)
		spiTransfer(displayBuffer[i]);

	DESELECT();
	SREG = sregBak;
}
