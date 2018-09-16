#include <avr/io.h>
#include "led.h"

void LED_init() {
	DDRD = (1 << DDD6);
}
