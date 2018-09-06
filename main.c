#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void led_init() {
	DDRB = (1 << PORTB0 | 1 << PORTB5);
}

void main (void) {
	led_init();
	uart_init();

	while (1) {
		led_control();
	}
}
