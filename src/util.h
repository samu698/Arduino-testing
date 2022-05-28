#pragma once
#include <stdint.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#ifdef __cplusplus
#define C_BEGIN extern "C" {
#define C_END }
#else
#define C_BEGIN
#define C_END
#endif

#define SECTION(x) __attribute__((section(#x)))
#define NOINLINE __attribute__((noinline))
#define NAKED __attribute__((naked))

#define cli() asm volatile ("cli")
#define sei() asm volatile ("sei")
#define nop() asm volatile ("nop")

#define bitMask(bit) (1 << bit)
#define readBit(value, bit) ((value & bitMask(bit)) == 1)
#define setBits(value, bits) (value |= bits)
#define clearBits(value, bits) (value &= ~(bits))

C_BEGIN
void utilMemset(void* buffer, uint8_t fill, uint16_t length);
C_END
