/*
 * Copyright (C) 2009 Chris McClelland
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "usart.h"

#define FOSC 16000000
#define BAUD 38400
#define MYUBRR ((FOSC/(16*BAUD))-1)

// Initialise the USART to 38400, 8-N-1
//
void usartInit() {
	UBRR1H = 0;									// Set the BAUD rate
	UBRR1L = (uint8)MYUBRR;
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UCSR1C = (3<<UCSZ10);
}

// Send byte on UART0
//
void usartSendByte(uint8 ch) {
	while ( !(UCSR1A & (1<<UDRE1)) );			// Wait until UART is ready
	UDR1 = ch;									// Send byte
}

// Send byte as two hex digits
//
void usartSendByteHex(uint8 byte) {
	uint8 ch;
	ch = byte >> 4;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = byte & 15;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
}

// Send long as four hex digits
//
void usartSendWordHex(uint16 word) {
	uint8 ch;
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
}

// Send long as four hex digits
//
void usartSendLongHex(uint32 word) {
	uint8 ch;
	ch = (word >> 28) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 24) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 20) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 16) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
}

void usartSendString(const char *s) {
	while ( *s ) {
		usartSendByte(*s++);
	}
}

void usartSendFlashString(const char *str) {
	char ch = pgm_read_byte(str);
	while ( ch ) {
		usartSendByte(ch);
		str++;
		ch = pgm_read_byte(str);
	}
}

// Wait for a character
//
uint8 usartGetByte() {
	while ( !(UCSR1A & (1<<RXC1)) );
	return UDR1;
}
