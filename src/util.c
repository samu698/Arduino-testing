#include "util.h"

void utilMemset(void* buffer, uint8_t fill, uint16_t length) {
	uint8_t* byteBuffer = (uint8_t*)buffer;
	for (uint16_t i = 0; i < length; i++)
		byteBuffer[i] = fill;	
}
