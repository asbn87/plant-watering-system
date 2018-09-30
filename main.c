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

uint8_t read_buffer[256];

uint8_t some_data[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
char myname[] = "Andreas";
uint8_t some_more_data[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

void main (void) {

	i2c_init();
	uart_init();

	memset(read_buffer, 0, 256);

	sei();

	_delay_ms(4000);

	eeprom_erase_memory();
	_delay_ms(1000);

	eeprom_write_buffer(some_data, 0x10, sizeof(some_data));
	_delay_ms(1000);
	eeprom_write_buffer(some_data, 0x33, sizeof(some_data));
	_delay_ms(1000);
	eeprom_write_buffer(some_data, 0x46, sizeof(some_data));
	_delay_ms(1000);
	eeprom_write_buffer(myname, 0x24, sizeof(myname));
	_delay_ms(1000);
	eeprom_write_buffer(some_more_data, 0x61, sizeof(some_more_data));
	_delay_ms(1000);

	eeprom_sequential_read(read_buffer, 0x00, 256);
	hexdump(read_buffer, 256);

	while (1) {

	}
}

