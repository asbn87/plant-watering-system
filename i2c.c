#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include <string.h>

#include "i2c.h"

void i2c_init(void) {
	TWBR = I2C_BITRATE;
}

void i2c_meaningful_status(uint8_t status) {
	switch (status) {
		case 0x08: // START transmitted, proceed to load SLA+W/R
			printf_P(PSTR("START\n"));
			break;
		case 0x10: // repeated START transmitted, proceed to load SLA+W/R
			printf_P(PSTR("RESTART\n"));
			break;
		case 0x38: // NAK or DATA ARBITRATION LOST
			printf_P(PSTR("NOARB/NAK\n"));
			break;
		// MASTER TRANSMIT
		case 0x18: // SLA+W transmitted, ACK received
			printf_P(PSTR("MT SLA+W, ACK\n"));
			break;
		case 0x20: // SLA+W transmitted, NAK received
			printf_P(PSTR("MT SLA+W, NAK\n"));
				break;
		case 0x28: // DATA transmitted, ACK received
			printf_P(PSTR("MT DATA+W, ACK\n"));
			break;
		case 0x30: // DATA transmitted, NAK received
			printf_P(PSTR("MT DATA+W, NAK\n"));
			break;
		// MASTER RECEIVE
		case 0x40: // SLA+R transmitted, ACK received
			printf_P(PSTR("MR SLA+R, ACK\n"));
			break;
		case 0x48: // SLA+R transmitted, NAK received
			printf_P(PSTR("MR SLA+R, NAK\n"));
			break;
		case 0x50: // DATA received, ACK sent
			printf_P(PSTR("MR DATA+R, ACK\n"));
			break;
		case 0x58: // DATA received, NAK sent
			printf_P(PSTR("MR DATA+R, NAK\n"));
			break;
		default:
			printf_P(PSTR("N/A %02X\n"), status);
			break;
	}
}

inline void i2c_wait_on_TWINT(void) {
	while (!(TWCR & (1 << TWINT)))
		;
}

inline void i2c_start() {
	TWCR = (1 << TWSTA | 1 << TWEN | 1 << TWINT);
	i2c_wait_on_TWINT();
}

inline void i2c_stop() {
	TWCR = (1 << TWSTO | 1 << TWEN | 1 << TWINT);
	_delay_us(50);
}

inline uint8_t i2c_get_status(void) {
	return TWSR & 0xF8;
}

inline void i2c_emit_addr(uint8_t address, uint8_t rw) {
	TWDR = address | rw;
	TWCR = (1 << TWEN | 1 << TWINT);
	i2c_wait_on_TWINT();
}

inline void i2c_emit_byte(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWEN | 1 << TWINT);
	i2c_wait_on_TWINT();
}

inline uint8_t i2c_read_ACK() {
	TWCR = (1 << TWEN | 1 << TWEA | 1 << TWINT);
	i2c_wait_on_TWINT();

	return TWDR;
}

inline uint8_t i2c_read_NAK() {
	TWCR = (1 << TWEN | 1 << TWINT);
	i2c_wait_on_TWINT();

	return TWDR;
}

inline void eeprom_wait_until_write_complete() {
	do {
		i2c_start();
		i2c_emit_addr(EEPROM_ADDR, I2C_W);
	} while (i2c_get_status() != MT_SLA_W_ACK);
}

uint8_t eeprom_read_byte(uint8_t addr) {
	uint8_t data;

	i2c_start();
	i2c_emit_addr(EEPROM_ADDR, I2C_W);
	i2c_emit_byte(addr);

	i2c_start();
	i2c_emit_addr(EEPROM_ADDR, I2C_R);
	data = i2c_read_NAK();
	i2c_stop();

	return data;
}

void eeprom_write_byte(uint8_t addr, uint8_t data) {
	i2c_start();
	i2c_emit_addr(EEPROM_ADDR, I2C_W);
	i2c_emit_byte(addr);
	i2c_emit_byte(data);
	i2c_stop();

	eeprom_wait_until_write_complete();

}

void eeprom_write_page(uint8_t *data, uint8_t start_addr, size_t len) {
	uint8_t *ptr = data;

	i2c_start();
	i2c_emit_addr(EEPROM_ADDR, I2C_W);
	i2c_emit_byte(start_addr);

	for (int i = 0; i < len; i++) {
		i2c_emit_byte(*(ptr++));
	}
	i2c_stop();

	eeprom_wait_until_write_complete();
}

void eeprom_sequential_read(uint8_t *buf, uint8_t start_addr, size_t len) {
	uint8_t ix = 0;
	uint8_t *ptr = buf;

	i2c_start();
	i2c_emit_addr(EEPROM_ADDR, I2C_W);
	i2c_emit_byte(start_addr);

	i2c_start();
	i2c_emit_addr(EEPROM_ADDR, I2C_R);

	do {
		*(ptr++) = i2c_read_ACK();
	} while (ix++ < len - 1);

	*ptr = i2c_read_NAK();

	i2c_stop();
}

void eeprom_erase_memory(void) {
	uint8_t buf[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	printf_P(PSTR("Erasing EEPROM\n"));
	for (uint8_t i=0; i<16; i++) {
		printf_P(PSTR(" > Erasing %02X-%02X\n"), 8*i, (8*i)+7);
		eeprom_write_page(buf, 0x08*i, 8);
	}
	printf_P(PSTR("Erase complete\n"));
}

void eeprom_write_buffer(uint8_t *buffer, uint8_t start_addr, size_t len) {
	uint8_t *data_ptr = buffer;
	uint8_t addr = start_addr;
	size_t slice_len = 0;
	size_t rem_len = len;

	if (addr + len >= 0x80) {
		printf_P(PSTR("ERROR, trying to write outside available EEPROM space: 0x%02x-0x%02x (0x00-0x80 valid)!\n"),
				addr, addr+len);
		return;
	}

	while (addr < start_addr + len) {

		if (addr % 8 != 0) {
			slice_len = 8 - (addr % 8);
		} else {
			slice_len = 8;
		}

		if (rem_len < slice_len) {
			slice_len = rem_len;
		}

		eeprom_write_page(data_ptr, addr, slice_len);

		addr += slice_len;
		data_ptr += slice_len;
		rem_len -= slice_len;
	}
}
