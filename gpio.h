#ifndef _GPIO_H_
#define _GPIO_H_

// Pump gives ~1dl/min
#define MOTOR_FLOWRATE_1DL 60
#define MOTOR_FLOWRATE_2DL 120

void gpio_init(void);

void motor_start(void);
void motor_stop(void);

#endif // _GPIO_H_
