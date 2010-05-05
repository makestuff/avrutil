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

// Initialise the USART to 8-N-1. If F_CPU is 16MHz, standard baud rates from 300-115200 work OK,
// but at 230400 and above the USART sampling error may be too great. If you want to use standard
// rates above that, you will need to use a 14.7456MHz crystal, which will support all standard
// rates up to 1843200.
//
void usartInit(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint32 baud)
{
	uint16 ubrr = F_CPU/(baud<<3) - 1;
	#ifdef __AVR_ATmega162__
	if ( usart == 0 ) {
		UBRR0H = ubrr>>8;							// Set the BAUD rate
		UBRR0L = ubrr&0x00FF;
		UCSR0A = (1<<U2X0);
		UCSR0B = (1<<RXEN0) | (1<<TXEN0);
		UCSR0C = (3<<UCSZ00) | (1<<URSEL0);
	} else
	#endif
	{
		UBRR1H = ubrr>>8;							// Set the BAUD rate
		UBRR1L = ubrr&0x00FF;
		UCSR1A = (1<<U2X1);
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);
		UCSR1C = (3<<UCSZ10)
		#ifdef __AVR_ATmega162__
			| (1<<URSEL0)
		#endif
			;
	}
}

// Send byte on UART0
//
void usartSendByte(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint8 ch)
{
	#ifdef __AVR_ATmega162__
	if ( usart == 0 ) {
		while ( !(UCSR0A & (1<<UDRE0)) );			// Wait until UART is ready
		UDR0 = ch;									// Send byte
	} else
	#endif
	{
		while ( !(UCSR1A & (1<<UDRE1)) );
		UDR1 = ch;
	}
}

// Send byte as two hex digits
//
void usartSendByteHex(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint8 byte)
{
	uint8 ch;
	ch = byte >> 4;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = byte & 15;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
}

// Send long as four hex digits
//
void usartSendWordHex(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
		uint16 word)
{
	uint8 ch;
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
}

// Send long as four hex digits
//
void usartSendLongHex(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
		uint32 word)
{
	uint8 ch;
	ch = (word >> 28) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 24) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 20) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 16) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(
	#ifdef __AVR_ATmega162__
		usart,
	#endif
		ch
	);
}

void usartSendString(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
		const char *s)
{
	while ( *s ) {
		usartSendByte(
		#ifdef __AVR_ATmega162__
			usart,
		#endif
			*s++
		);
	}
}

void usartSendFlashString(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
		const char *str)
{
	char ch = pgm_read_byte(str);
	while ( ch ) {
		usartSendByte(
		#ifdef __AVR_ATmega162__
			usart,
		#endif
			ch
		);
		str++;
		ch = pgm_read_byte(str);
	}
}

// Wait for a character
//
uint8 usartGetByte(
	#ifdef __AVR_ATmega162__
		uint8 usart
	#endif
	)
{
	#ifdef __AVR_ATmega162__
	if ( usart == 0 ) {
		while ( !(UCSR0A & (1<<RXC0)) );			// Wait until UART is ready
		return(UDR0);								// Get byte
	} else
	#endif
	{
		while ( !(UCSR1A & (1<<RXC1)) );
		return(UDR1);
	}
}
