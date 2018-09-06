#include <avr/io.h>

#include "serial.h"

void uart_init(void) {
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)(UBRR);
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0 | 1 << RXEN0);
	UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);

}

void uart_putchar(char chr) {
	if (chr == '\n') {
		uart_putchar('\r');
	}
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = chr;
}
void uart_putstr(const char *str) {
	while(*str) {
		uart_putchar(*str++);
	}
}

char uart_getchar(void) {
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}

void uart_echo(void) {
	uart_putchar(uart_getchar());
}
