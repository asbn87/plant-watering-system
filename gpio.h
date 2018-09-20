#ifndef _GPIO_H_
#define _GPIO_H_

void gpio_init(void);

uint8_t button_pressed(void);

uint8_t simple_ramp(void);
uint8_t pot_control(void);
uint8_t blink(void);
uint8_t led_off(void);

#endif // _GPIO_H_

