#pragma once

#define BAUD 9600

#include "util.h"

C_BEGIN
void serialSetup();
void serialWrite(uint8_t byte);
void serialWriteBuffer(uint8_t* data, uint16_t length);
void serialPrintUNum(uint64_t unsingedNum);
C_END
