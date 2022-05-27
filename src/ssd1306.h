#pragma once

#include "util.h"
#include "pins.h"

#ifndef SSD1306_DC
#define SSD1306_DC D6
#endif

#ifndef SSD1306_CS
#define SSD1306_CS D7
#endif

#define DWIDTH 128
#define DHEIGHT 64

C_BEGIN
void setupSsd1306();

void setPixel(uint8_t x, uint8_t y);
void clearPixel(uint8_t x, uint8_t y);
void invertPixel(uint8_t x, uint8_t y);
void clearDisplay();

void display();
C_END
