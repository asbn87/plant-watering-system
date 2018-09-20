#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"
#include "gpio.h"

void gpio_init() {
	/*
	 * N/O active high button connected to PD2
	 */
	DDRD &= ~(1 << DDD2);

	/*
	 * PD6/OC0A used for PWM'ed LED output
	 */
	DDRD |= (1 << DDD6);
}

uint8_t button_pressed() {
	static uint8_t prev_btn_state = 0;

	if ((PIND & (1 << PIND2)) && prev_btn_state == 0) {
		prev_btn_state = 1;

	} else if (!(PIND & (1 << PIND2)) && prev_btn_state == 1) {
		prev_btn_state = 0;
		return 1;
	}
	return 0;
}

uint8_t simple_ramp() {
	static uint8_t fade = 0;
	static int8_t dir = -1;

	if (fade == 0xff || fade == 0x00) {
		dir *= -1;
	}
	fade += dir;
	return fade;
}

uint8_t pot_control(void) {
	return get_adc_value();
}

uint8_t blink() {
	static uint8_t counter = 0;
	static uint8_t ret_val = 0;

	if (counter++ == 100) {
		counter = 0;
		ret_val = ret_val == 255 ? 0 : 255;
	}
	return ret_val;
}

uint8_t led_off() {
	return 0;
}
