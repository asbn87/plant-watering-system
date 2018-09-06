#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void led_init() {
	DDRB = (1 << PORTB0);
}

void main (void) {

	while (1) {
		PORTB |= (1 << PORTB0);
		_delay_ms(500);
		PORTB &= ~(1 << PORTB0);
		_delay_ms(500);
	}
}
