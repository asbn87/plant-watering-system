#include <avr/io.h>

#include "timer.h"

void timer_init() {
	// CTC mode
	TCCR0A |= (1 << WGM01);

	// Prescaler = 1024
	TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);

	// Period of 10 ms / 100 Hz
	OCR0A = 77;
}

