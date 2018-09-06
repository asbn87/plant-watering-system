#include <avr/io.h>
#include <string.h>

#include "serial.h"

#define BUF_LEN 4
char chr_buf[BUF_LEN];

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
		uart_putchar(*str);
		str++;
	}
}

char uart_getchar(void) {
	char chr;
	while (!(UCSR0A & (1 << RXC0)))
		;
	chr = UDR0;
	return chr;
}

void uart_echo(void) {
	uart_putchar(uart_getchar());
}

void uart_getstr(char *buf, uint8_t max_len) {
	uint8_t ix = 0;
	// clear the buffer to get rid of old crap
	memset(buf, 0, max_len);

	while(1) {
		buf[ix] = uart_getchar();
		// catch overruns by checking length as well as command complete/CR
		// note that we ignore the whitespace here
		if (buf[ix] == '\r' || ix == max_len-1) {
			break;
		}
		// echo the char for usability
		uart_putchar(buf[ix]);
		ix++;
	}
	// add newline for prettyness
	uart_putchar('\n');
}


void led_control(void) {
	// print prompt
	uart_putstr(" > ");

	// get cr-terminated string from UART
	uart_getstr(chr_buf, BUF_LEN);

	// check for ON option
	if (strncmp("ON", chr_buf, 2) == 0) {
		PORTB |= (1 << PORTB0);
		uart_putstr("led on\n");
	// check for OFF option
	} else if (strncmp("OFF", chr_buf, 3) == 0) {
		PORTB &= ~(1 << PORTB0);
		uart_putstr("led off\n");
	// catch the rest, print a response and then ignore
	} else {
		uart_putstr("invalid command\n");
	}
}
