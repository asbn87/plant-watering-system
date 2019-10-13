#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "serial.h"
#include "timer.h"
#include "util.h"

uint8_t timer2_ovf_cntr = 0;
uint8_t timer2_sec_cntr = 0;
volatile uint8_t soilsensor_sleep_flag = 0;
volatile uint8_t motor_flow_flag = 0;

ISR(TIMER2_COMPA_vect) {
	timer2_ovf_cntr++; // Increment overflow counter

	// Executes every second
	if(timer2_ovf_cntr >= TIMER2_OVF_SEC) {
		timer2_sec_cntr++;

		// Give 1 dl of water
		if(motor_flow_flag == 1) {
			if(timer2_sec_cntr >= MOTOR_FLOWRATE_1DL) {
				timer2_sec_cntr = 0;
				soilsensor_sleep_flag = 0;
				motor_flow_flag = 0;
			}
		}
		// Give 2dl of water
		else if(motor_flow_flag == 2) {
			if(timer2_sec_cntr >= MOTOR_FLOWRATE_2DL) {
				timer2_sec_cntr = 0;
				soilsensor_sleep_flag = 0;
				motor_flow_flag = 0;
			}
		}
		// Sleep before checking moisture values again
		else {
			if(timer2_sec_cntr >= SOILSENSOR_READ_DURATION) {
				timer2_sec_cntr = 0;
				soilsensor_sleep_flag = 0;
			}
		}

		// When second is reached reset overflow counter
		timer2_ovf_cntr = 0;
	}
}

void main (void) {
	uart_init();
	_delay_ms(50); // Just to not show any crap output in serial monitor on start..
	printf("--Plant watering system initation--\n");
	printf("Initiating I2C interface..\n");
	i2c_init();
	printf("Initiating Timer..\n");
	timer_init();
	sei(); // Enable interrupts

	uint8_t buf[2];
	uint16_t data;

	while (1) {
		if(soilsensor_sleep_flag != 1) {
			// Get moisture value
			printf("\n--Reading from soil sensor--\n");
			soilsensor_read_moisture(buf, SOILSENSOR_TOUCH_BASE, SOILSENSOR_TOUCH_CHANNEL_OFFSET, 2);
			data = ((uint16_t)buf[0] << 8) | buf[1];

			if(data >= MOISTURE_MIN_VALUE) {
				printf("Plant: I'm not thirsty..\n");
				printf("Moisture: %d\n\n", data);
			}

			else if(data >= MOISTURE_CRITICAL_VALUE && data < MOISTURE_MIN_VALUE) {
				printf("Plant: Ok, I'll just have one little sip!\n");
				printf("Moisture: %d\n\n", data);
				printf("System: Motor starts\n");
				printf("System: Flowrate, 1dl\n");
				motor_flow_flag = 1;
				motor_start(); // Start the pump

				while(motor_flow_flag != 0)
					;

				printf("System: Motor stops\n");
				motor_stop(); // Stop the pump
			}

			else {
				printf("Plant: Seriously? Give me water, PLEASE!\n");
				printf("Moisture: %d\n\n", data);
				printf("System: Motor starts\n");
				printf("System: Flowrate, 2dl\n");
				motor_flow_flag = 2;
				motor_start(); // Start the pump

				while(motor_flow_flag != 0)
					;

				motor_stop(); // Stop the pump
			}
			printf("System: Next read in %d seconds\n", SOILSENSOR_READ_DURATION);
			soilsensor_sleep_flag = 1;
		}
	}
}
