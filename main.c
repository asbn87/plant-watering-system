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
		OCR0A = 255;
		_delay_ms(500);
		OCR0A = 50;
		_delay_ms(500);
		OCR0A = 200;
		_delay_ms(500);
		OCR0A = 100;
		_delay_ms(500);
		OCR0A = 150;
		_delay_ms(500);
		OCR0A = 0;
	}
}

