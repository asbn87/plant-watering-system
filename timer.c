#include <avr/io.h>

#include "timer.h"

void timer_init() {

	/*
	 * Timer 2 --- systick
	 *
	 * CTC mode
	 * period = 16 ms / freq = 62.5 Hz
	 * Prescaler 1024
	 */
	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
	TIMSK2 |= (1 << OCIE2A);
	OCR2A = 77;
}

