#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "motor.h"

/* ATMega328p - L293D */
// PIN9 / PB1 = Enable1 // On/Off, PWM enabled can be used to control flow speed with potentiometer
// PIN8 / PB0 = Input1 // Forward flow
// PIN7 / PD7 = Input2 // Backward flow

/* DC motor - L293D */
// DC+ = Output1
// DC- = Output2

void motor_init(void) {
	DDRB &= ~(1 << PB0);
	DDRD &= ~(1 << PD7);
}

void motor_start(void) {
	PORTB |= (1 << PB0);
	PORTB |= (1 << PB1);
}

void motor_stop(void) {
	PORTB &= ~(1 << PB0);
	PORTB &= ~(1 << PB1);
}

void motor_wait_until_watering_complete(void) {
	// ...
}
