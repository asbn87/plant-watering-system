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
#include "motor.h"

void main (void) {

	motor_init();
	i2c_init();
	uart_init();

	/* Start motor and give a certain dosage.
	motor_start();
	_delay_ms(flowrate); // motor_wait_until_watering_complete(void)
	motor_stop();
	*/

	/* Read byte from soil moisture sensor
	printf("Data: %d", soilsensor_read_byte(0x0F));
	printf("Data: %d", soilsensor_read_byte(0x10));
	*/

	/* Read from soil moisture sensor
	buf[2];
	uint8_t buf_cntr = 0;
	soilsensor_read(buf, 0x0F, 2);

	while(buf_cntr < sizeof(buf)) {
		printf("Data: %d\n", buf[buf_cntr++]);
	}
	*/

	while (1) {
		// ...
	}
}
