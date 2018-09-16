#include <avr/io.h>
#include "led.h"

void LED_init() {
	DDRB = (1 << DDB0);
}
