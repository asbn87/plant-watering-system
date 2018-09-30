#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

void hexdump(uint8_t *buffer, size_t max_len) {
	uint16_t ix = 0;

	char cbuf[] = "........";

	do {
		printf_P(PSTR("%04X  |  "), ix);
		do  {
			printf_P(PSTR("%02X "), buffer[ix]);
			cbuf[ix%8] = (buffer[ix] >= 32 && buffer[ix] < 127) ? buffer[ix] : '.';
			ix++;
		} while (ix % 8 != 0 && ix < max_len);

		printf_P(PSTR(" | %s |\n"), cbuf);

	} while (ix < max_len);
}
