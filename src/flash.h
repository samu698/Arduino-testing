#pragma once
#include "util.h"

C_BEGIN
void writePage(const uint8_t* pageBuffer, uint16_t pageN);
void readPage(uint8_t* pageBuffer, uint16_t pageN);
C_END
