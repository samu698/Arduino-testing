#pragma once

#include "util.h"

#define SSD1306_DC 6
#define SSD1306_CS 7

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
