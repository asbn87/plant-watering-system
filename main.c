#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "gpio.h"
#include "serial.h"
#include "timer.h"

ISR(TIMER2_COMPA_vect) {
	check_button();
}
void main (void) {

	gpio_init();
	uart_init();
	timer_init();

	sei();

	while (1) {

	}
}

