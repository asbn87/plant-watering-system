#include <avr/io.h>

#include "timer.h"

void timer_init() {
	// Fast PWM mode, 'Clear OC0A on match, set OC0A on BOTTOM'
	TCCR0A |= (1 << COM0A1 | 1 << WGM01 | 1 << WGM00);

	// Prescaler = 64
	TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);

	OCR0A = 0;
}

