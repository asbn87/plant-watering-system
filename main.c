#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

ISR(TIMER2_COMPA_vect) {
	OCR0A = simple_ramp();
}

void main (void) {

	LED_init();
	uart_init();
	timer_init();

	sei();

	while (1) {
		;
	}
}

