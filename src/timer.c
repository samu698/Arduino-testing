#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// * * * * * * * * * *
// * TEST THIS CODE  *
// * * * * * * * * * *

// Check if F_CPU is a multiple of 8000000
// And if it is use the timer prescaler
#if ((F_CPU / 8000000) * 8000000) == F_CPU
#define USING_PRESCALER
#define COUNTS_TO_US(x) (x * 8000000) / F_CPU
#else
#define COUNTS_TO_US(x) (x * 1000000) / F_CPU
#endif

uint64_t micros;

void timerBegin() {
	cli();

	clearBits(TCCR0A, bitMask(COM0A0) | bitMask(COM0A1)); // Set normal input timer mode
	clearBits(TCCR0A, bitMask(COM0B0) | bitMask(COM0B1)); // Set normal output timer mode
	
	// Set no pwm output
	clearBits(TCCR0A, bitMask(WGM00) | bitMask(WGM01));
	clearBits(TCCR0B, bitMask(WGM02));

	setBits(TIMSK0, bitMask(TOIE0)); // Enable the timer overflow interrupt

	micros = 0;
	TCNT0 = 0; // Clear the timer register

	// Set the timer clock source
#ifdef USING_PRESCALER
	// clk / 8
	setBits(TCCR0B, bitMask(CS01));
	clearBits(TCCR0B, bitMask(CS00) | bitMask(CS02));
#else
	// clk
	setBits(TCCR0B, bitMask(CS00));
	clearBits(TCCR0B, bitMask(CS01) | bitMask(CS02));
#endif

	sei();
}

void timerStop() {
	clearBits(TCCR0B, bitMask(CS00) | bitMask(CS01) | bitMask(CS02)); // Disable the timer
	clearBits(TIMSK0, bitMask(TOIE0)); // Disable the timer overflow interrupt
}

uint64_t timerMicros() {
	cli();
	uint64_t time = micros + COUNTS_TO_US(TCNT0);
	sei();
	return time;
}

uint64_t timerMillis() {
	cli();
	uint64_t time = (micros + COUNTS_TO_US(TCNT0)) / 1000;
	sei();
	return time;
}

ISR(TIMER0_OVF_vect) {
	micros += COUNTS_TO_US(256);
}
