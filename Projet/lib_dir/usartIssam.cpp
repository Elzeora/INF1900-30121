#include "usartIssam.h"
#include <avr/io.h>

#define BAUDS 0xCF; // 2400 bauds

void initUSART(void) {
	UBRR0H = 0;
	UBRR0L = BAUDS;
	// Enable reveiver and transmitter
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	// 8 bits
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

char receiveChar(void) {
	while (!(UCSR0A & _BV(RXC0)))
		;
	return UDR0;
}

void printChar(char data) {
	while (!(UCSR0A & _BV(UDRE0)))
		;
	UDR0 = data;
}

void printChars(const char *s) {
	do {
		printChar(*s);
	} while (*++s != '\0');
}
