#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"
#include "gpio.h"
#include "serial.h"
#include "timer.h"

enum LED_mode_t {
	LED_FADE = 0,
	LED_POT_CTRL = 1,
	LED_BLINK = 2,
	LED_OFF = 3,
	LED_NDEF = 4,
};

volatile enum LED_mode_t state = LED_FADE;
uint8_t (*led_control_function)(void) = &simple_ramp;

void update_state(void);
void update_state() {

	if (button_pressed() == 1) {

		// Handle state wrap-around
		if (++state >= LED_NDEF) {
			state = LED_FADE;
		}

		// If a state switch occured, update the led control func ptr
		switch (state) {

			case LED_FADE:
				led_control_function = &simple_ramp;
				break;

			case LED_POT_CTRL:
				led_control_function = &pot_control;
				break;

			case LED_BLINK:
				led_control_function = &blink;
				break;

			case LED_OFF:
			case LED_NDEF:
				led_control_function = &led_off;
				break;
		}
	}
}

ISR(TIMER2_COMPA_vect) {
	ADCSRA |= (1 << ADSC);
	update_state();
	OCR0A = led_control_function();
}

ISR(ADC_vect) {
	set_adc_value(ADCH);
}

void main (void) {

	adc_init();
	gpio_init();
	timer_init();
	uart_init();

	sei();

	while (1) {

	}
}

