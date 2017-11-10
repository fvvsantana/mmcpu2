# Makefile - Main Makefile
#
#   Copyright 2017  Monaco F. J.   <monaco@icmc.usp.br>
#
#   This file is part of Muticlycle Mips CPU (MMCPU)
#
#   MMCPU is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

# User customizations
# Edit if you need somethig different from the defaults.

CC = gcc
AR = ar
ARFLAGS = rcs
PREFIX = /tmp#

# Project settings.
# You need not (and should probably not) change bellow this line.

BIN = cpu
OBJECTS = cpu.o code.o
LIB = libmmcpu.a
LIB_OBJECTS = cpu.o
LIB_HEADERS = cpu.h
PROJECT= mmcpu#

all : $(BIN) $(LIB)

$(BIN) : $(OBJECTS) 
	$(CC) $^ -o $@

$(LIB) : $(LIB_OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< 

%.d : %.c
	$(CC) $(CPPFLAGA) $(CFLAGS) -MM -MT '$(<:%.c=%.o) $@' $< -o $@

deps = $(OBJECTS:%.o=%.d)

include $(deps)

.PHONY : clean install

clean:
	rm -f $(LDFLAGS) $(OBJECTS) $(BIN) $(LIB) $(deps) *~ \#*

install: $(LIB)
	install -d $(PREFIX)/lib
	install -d $(PREFIX)/include/$(PROJECT)
	cp $^ $(PREFIX)/lib/
	cp $(LIB_HEADERS) $(PREFIX)/include/$(PROJECT)/

uninstall:
	rm -f $(PREFIX)/lib/$(LIB)
	rm -f $(PREFIX)/include/$(PROJECT)/$(LIB)
