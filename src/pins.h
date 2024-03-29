#pragma once

#include <avr/io.h>

#define MK_PIN(PORT, PIN) (((uint16_t)(&PORT) & 0xFF) | (PIN & 0xFF) << 8)
#define D0 MK_PIN(PORTD, 0)
#define D1 MK_PIN(PORTD, 1)
#define D2 MK_PIN(PORTD, 2)
#define D3 MK_PIN(PORTD, 3)
#define D4 MK_PIN(PORTD, 4)
#define D5 MK_PIN(PORTD, 5)
#define D6 MK_PIN(PORTD, 6)
#define D7 MK_PIN(PORTD, 7)
#define D8 MK_PIN(PORTB, 0)
#define D9 MK_PIN(PORTB, 1)
#define D10 MK_PIN(PORTB, 2)
#define D11 MK_PIN(PORTB, 3)
#define D12 MK_PIN(PORTB, 4)
#define D13 MK_PIN(PORTB, 5)
#define A0 MK_PIN(PORTC, 0)
#define A1 MK_PIN(PORTC, 1)
#define A2 MK_PIN(PORTC, 2)
#define A3 MK_PIN(PORTC, 3)
#define A4 MK_PIN(PORTC, 4)
#define A5 MK_PIN(PORTC, 5)

#define PIN_MOSI D11
#define PIN_MISO D12
#define PIN_CLK D13

#define PIN_PORT(PIN) (*(volatile uint8_t*)(PIN & 0xFF))
#define PIN_DDR(PIN) (*(volatile uint8_t*)((PIN & 0xFF) - 1))
#define PIN_PIN(PIN) (*(volatile uint8_t*)((PIN & 0xFF) - 2))
#define PIN_BIT(PIN) ((PIN >> 8) & 0xFF)

#define pinOn(PIN) (PIN_PORT(PIN) |= (1 << PIN_BIT(PIN)))
#define pinOff(PIN) (PIN_PORT(PIN) &= ~(1 << PIN_BIT(PIN)))
#define pinOutput(PIN) (PIN_DDR(PIN) |= (1 << PIN_BIT(PIN)))
#define pinInput(PIN) (PIN_DDR(PIN) &= ~(1 << PIN_BIT(PIN)))
#define pinRead(PIN) ((PIN_PIN(PIN) & PIN_BIT(PIN)) != 0)
