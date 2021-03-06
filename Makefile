#
# Copyright (C) 2009-2012 Chris McClelland
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
PLATFORM = avr
TARGET = lib/$(PLATFORM)/$(MCU)/avrutil.a
MCU = at90usb162
F_CPU = 16000000

OBJDIR = .build
DEPDIR = .deps
CC_SRCS = $(shell ls *.c)
CC_OBJS = $(CC_SRCS:%.c=$(OBJDIR)/$(PLATFORM)/$(MCU)/%.o)
CC = avr-gcc
AR = avr-ar
CFLAGS = \
	-O3 -mmcu=$(MCU) -funsigned-char -funsigned-bitfields -ffunction-sections \
	-fpack-struct -fshort-enums -finline-limit=20 -Wall -Wstrict-prototypes \
	-Wundef -std=gnu99 -Wall -pedantic-errors -I../../common

all: $(TARGET)

$(TARGET): $(CC_OBJS)
	mkdir -p lib/$(PLATFORM)/$(MCU)
	$(AR) cr $@ $^

$(OBJDIR)/$(PLATFORM)/$(MCU)/%.o : %.c
	$(CC) -c $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$(PLATFORM)/$(@F).d -Wa,-adhlns=$(OBJDIR)/$(PLATFORM)/$<.lst $< -o $@ -DF_CPU=$(F_CPU)

clean: FORCE
	rm -rf $(OBJDIR) $(DEPDIR) lib Debug Release *.ncb *.suo *.user

-include $(shell mkdir -p $(OBJDIR)/$(PLATFORM)/$(MCU) $(DEPDIR)/$(PLATFORM)/$(MCU) 2>/dev/null) $(wildcard $(DEPDIR)/$(PLATFORM)/$(MCU)/*)

FORCE: