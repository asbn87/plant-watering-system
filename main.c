#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

void led_init() {
	DDRB = (1 << PORTB0);
}

void main (void) {
	uart_init();

	while (1) {
		uart_echo();
	}
}
