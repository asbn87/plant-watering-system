#include <avr/io.h>

#include "timer.h"

void timer_init() {
	/*
	 * Timer 0 --- PWM
	 *
	 * Fast PWM mode,
	 * 'Clear OC0A on match, set OC0A on BOTTOM'
	 * Prescaler = 64
	 * freq = 976 Hz
	 */
	TCCR0A |= (1 << COM0A1 | 1 << WGM01 | 1 << WGM00);
	TCCR0B |= (0 << CS02 | 1 << CS01 | 1 << CS00);
	OCR0A = 0;

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
	OCR2A = 124;
}

