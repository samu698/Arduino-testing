#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// * * * * * * * * * *
// * TEST THIS CODE  *
// * * * * * * * * * *

// Check if F_CPU is a multiple of 8000000
#if ((F_CPU / 8000000) * 8000000) == F_CPU
#define USING_PRESCALER
#define COUNTS_TO_US(x) (x * 8000000) / F_CPU
#else
#define COUNTS_TO_US(x) (x * 1000000) / F_CPU
#endif

uint64_t micros;

void timerBegin() {
	cli();

	TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1)); // Set normal input timer mode
	TCCR0A &= ~((1 << COM0B0) | (1 << COM0B1)); // Set normal output timer mode
	
	// Set no pwm output
	TCCR0A &= ~((1 << WGM00) | (1 << WGM01));
	TCCR0B &= ~(1 << WGM02);

	TIMSK0 |= 1 << TOIE0; // Enable the timer overflow interrupt

	micros = 0;
	TCNT0 = 0; // clear the timer register

	// Set the timer clock source
#ifdef USING_PRESCALER
	// clk / 8
	TCCR0B |= 1 << CS01;
	TCCR0B &= ~((1 << CS00) | (1 << CS02));
#else
	// clk
	TCCR0B |= 1 << CS00;
	TCCR0B &= ~((1 << CS01) | (1 << CS02));
#endif

	sei();
}

void timerStop() {
	TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
	TIMSK0 |= 1 << TOIE0; // disable the timer overflow interrupt
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
