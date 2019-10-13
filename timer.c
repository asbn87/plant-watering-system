#include <avr/io.h>

#include "timer.h"

void timer_init() {
	//Timer2
	TCCR2A |= (1 << WGM21); // CTC mode
	TCCR2A |= (1 << COM2A1); // Clear OC0A on compare match, set OC0A at BOTTOM (non-inverted)
	OCR2A = 255; // Set to MAX
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Set prescaler to 1024 and start the timer
	TIMSK2 |= (1 << OCIE2A); // Enable output compare A match interrupt
}
