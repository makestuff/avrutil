/*
 * Copyright (C) 2009-2012 Chris McClelland
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef USART_H
#define USART_H

#include "makestuff.h"

void usartInit(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint32 baud
);
void usartSendByte(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint8 ch
);
void usartSendByteHex(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint8 ch
);
void usartSendWordHex(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint16 ch
);
void usartSendLongHex(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	uint32 word
);
void usartSendString(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	const char *s
);
void usartSendFlashString(
	#ifdef __AVR_ATmega162__
		uint8 usart,
	#endif
	const char *s
);
uint8 usartGetByte(
	#ifdef __AVR_ATmega162__
		uint8 usart
	#else
		void
	#endif
);

#endif
