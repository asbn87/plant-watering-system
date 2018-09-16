#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

void main (void) {
	uint8_t counter = 0;

	uart_init();
	timer_init();
	LED_init();

	while (1) {
		while(!(TIFR0 & (1 << OCF0A)))
			;
		TIFR0 |= (1 << OCF0A);

		if (counter++ == 10){
			PORTB ^= (1 << PORTB0);
			counter = 0;
		}
	}
}

