#pragma once

#include "util.h"

#define PIN_SPI_SS 10
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13

#define BITRATE		8000000
#define BIT_ORDER	MSBFIRST
#define SPI_MODE	SPI_MODE0

C_BEGIN
void setupSpi();
uint8_t spiTransfer(uint8_t data);
C_END
