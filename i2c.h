#ifndef _I2C_H_
#define _I2C_H_

// I2C Read/Write flags
#define I2C_R	1
#define I2C_W	0


void i2c_init(void);

void i2c_start(void);
void i2c_stop(void);

uint8_t i2c_get_status(void);
void i2c_meaningful_status(uint8_t status);

void i2c_xmit_addr(uint8_t address, uint8_t rw);
void i2c_xmit_byte(uint8_t data);

void eeprom_wait_until_write_complete(void);

uint8_t eeprom_read_byte(uint8_t addr);
void eeprom_write_byte(uint8_t addr, uint8_t data);

void eeprom_write_page(uint8_t addr, uint8_t *data);
void eeprom_sequential_read(uint8_t *buf, uint8_t start_addr, uint8_t len);

#endif // _I2C_H_
