#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "gpio.h"

void gpio_init() {
	DDRD &= ~(1 << PIND2);
}

void check_button(void) {
	static uint8_t prev_btn_state = 0;

	if ((PIND & (1 << PIND2)) && prev_btn_state == 0) {
		printf_P(PSTR("pushed\n"));
		prev_btn_state = 1;

	} else if (!(PIND & (1 << PIND2)) && prev_btn_state == 1) {
		printf_P(PSTR("released\n"));
		prev_btn_state = 0;
	}
}
uint8_t simple_ramp() {
	// ...
}
