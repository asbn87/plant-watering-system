#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "adc.h"
#include "gpio.h"
#include "serial.h"
#include "timer.h"

volatile uint8_t adc_value = 0;

ISR(TIMER2_COMPA_vect) {
	check_button();
	ADCSRA |= (1 << ADSC);
	OCR0A = adc_value;
}

ISR(ADC_vect) {
	adc_value = ADCH;
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

