#include <avr/io.h>
#include "led.h"

void LED_init() {
	DDRD = (1 << DDD6);
}

uint8_t simple_ramp() {
	static uint8_t counter = 1;
	static int8_t direction = 1;

	if (counter == 0 || counter == 255) {
		direction *= -1;
	}
	counter += direction;
	return counter;
}
