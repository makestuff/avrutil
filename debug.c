/* 
 * Copyright (C) 2012 Chris McClelland
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
#include <util/delay_basic.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "makestuff.h"

// sudo minicom -b 115200 -D /dev/ttyS0 -o -w -8
#define DEBUG_MASK (1<<2)
#define DEBUG_PORT C
#define DEBUG_BAUD 45

#define OUT_PORT CONCAT(PORT, DEBUG_PORT)
#define DDR_PORT CONCAT(DDR, DEBUG_PORT)

void debugInit(void) {
	DDR_PORT |= DEBUG_MASK;
}

void debugSendByte(uint8 byte) {
	uint8 hi, lo;
	cli();
	hi = OUT_PORT | DEBUG_MASK;
	lo = OUT_PORT & (~DEBUG_MASK);
	OUT_PORT = lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x01) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x02) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x04) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x08) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x10) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x20) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x40) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = (byte & 0x80) ? hi : lo;
	_delay_loop_1(DEBUG_BAUD);
	OUT_PORT = hi;
	_delay_loop_1(DEBUG_BAUD);
	sei();
}

void debugSendByteHex(uint8 byte) {
	uint8 ch;
	ch = (byte >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = byte & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
}

void debugSendWordHex(uint16 word) {
	uint8 ch;
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
}

void debugSendLongHex(uint32 word) {
	uint8 ch;
	ch = (word >> 28) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 24) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 20) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 16) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	debugSendByte(ch);
}

void debugSendRamString(const char *str) {
	while ( *str ) {
		debugSendByte(*str++);
	}
}

void debugSendFlashString(const char *str) {
	char ch = pgm_read_byte(str);
	while ( ch ) {
		debugSendByte(ch);
		str++;
		ch = pgm_read_byte(str);
	}
}
