#ifndef _I2C_H_
#define _I2C_H_

#define I2C_FREQ 100000
#define I2C_BITRATE ((F_CPU / I2C_FREQ) - 16) / 2 + 1

#define EEPROM_ADDR 0xA0

#define SOILSENSOR_ADDR 0x36
#define SOILSENSOR_TOUCH_BASE 0x0F // Module base address
#define SOILSENSOR_TOUCH_CHANNEL_OFFSET 0x10 // Touch module function address register
#define SOILSENSOR_READ_DURATION 3600 // Duration of readings in seconds

#define MOISTURE_MIN_VALUE 800 // Moisture value minimum
#define MOISTURE_CRITICAL_VALUE 500 // Critical level to double the dosage

#define MT_SLA_W_ACK 0x18

// I2C Read/Write flags
#define I2C_R	1
#define I2C_W	0


void i2c_init(void);

void i2c_start(void);
void i2c_stop(void);

uint8_t i2c_get_status(void);
void i2c_meaningful_status(uint8_t status);

void i2c_emit_addr(uint8_t address, uint8_t rw);
void i2c_emit_byte(uint8_t data);

void eeprom_wait_until_write_complete(void);

uint8_t eeprom_read_byte(uint8_t addr);
void eeprom_write_byte(uint8_t addr, uint8_t data);

void eeprom_write_page(uint8_t *data, uint8_t start_addr, size_t len);
void eeprom_sequential_read(uint8_t *buf, uint8_t start_addr, size_t len);

void eeprom_erase_memory(void);
void eeprom_write_buffer(uint8_t *buffer, uint8_t start_addr, size_t len);

void soilsensor_read_moisture(uint8_t *buf, uint8_t regHigh, uint8_t regLow, uint8_t len);

#endif // _I2C_H_
