# Makefile - Main Makefile
#
#   Copyright 2017  Your Name(s)   <your email(s)>
#
#   This file is part of YourProject
#
#   YourProject is free software: you can redistribute it and/or modify
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

BIN = mycpu
OBJECTS = code.o
LIB = libmmcpu.a
PROJECT= myproj#
DIST = dist#

CPP_FLAGS = -I.
LD_FLAGS = -L.
C_FLAGS =

all : $(BIN) 

$(BIN) : $(OBJECTS) 
	$(CC) $(LD_FLAGS) $(LDFLAGS) $^ -o $@ -l$(LIB:lib%.a=%)

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CPP_FLAGS) $(C_FLAGS) -c $< 

%.d : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CPP_FLAGS) $(C_FLAGS) -MM -MT '$(<:%.c=%.o) $@' $< -o $@

deps = $(OBJECTS:%.o=%.d) 

NO_D :=
NO_D := $(or $(NO_D), $(findstring clean,$(MAKECMDGOALS)))
ifeq (,$(NO_D))
include $(deps)
endif

.PHONY : clean dist

clean:
	rm -f $(OBJECTS) $(BIN) $(LIB) $(LIB_OBJECTS) $(deps) *~ \#*

dist:  $(BIN) COPYING
	if test -d $(DIST) ; then rm -rf $(DIST) ; fi
	install -d $(DIST)/$(PROJECT)
	cp $(OBJECTS:%.o=%.c) $(DIST)/$(PROJECT)
	cp COPYING $(DIST)/$(PROJECT)
	cp Makefile $(DIST)/$(PROJECT)
	tar --directory $(DIST) -zcvf $(PROJECT).tar.gz $(PROJECT)

COPYING :
	@echo "***"
	@echo "Please, copy GPL vr3 text into a file named COPYING"
	@echo "GPL v3 may by found at http://gnu.org/licenses/gpl.txt"
	@echo "If you have wget installed you may just run"
	@echo "wget http://gnu.org/licenses/gpl.txt && mv gpl.txt COPYING"
	@echo "Alternatively, you may find a copy of GPL file with mmcpu project"
	@echo "***"
	exit 1
