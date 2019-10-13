#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "gpio.h"

void gpio_init() {
	// ...
}

void motor_start(void) {
	PORTB |= (1 << PB0); // Initiate Input1, forward flow
	PORTB |= (1 << PB1); // Pump on
}

void motor_stop(void) {
	PORTB &= ~(1 << PB0); // Stop forward flow
	PORTB &= ~(1 << PB1); // Pump off
}
