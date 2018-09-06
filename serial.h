#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUDRATE 38400
#define UBRR (F_CPU/16/BAUDRATE-1)

void uart_init(void);

void uart_putchar(char chr);
void uart_putstr(const char *str);

char uart_getchar(void);

void uart_echo(void);

#endif

