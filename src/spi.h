#pragma once

#include "util.h"

#define BITRATE		8000000
#define BIT_ORDER	MSBFIRST
#define SPI_MODE	SPI_MODE0

C_BEGIN
void setupSpi();
uint8_t spiTransfer(uint8_t data);
C_END
