##   Makefile.am - Automake script for project's libraries.
##
##   Copyright (c) 2014, Francisco Jose Monaco  <moanco@icmc.usp.br>
##
##   This file is part of MMCPU.
##
##   MMCPU is free software: you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation, either version 3 of the License, or
##   (at your option) any later version.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Reminder for versioning
##
## Versioning: CURRENT:REVISION:AGE
## CURRENT The latest interface implemented.
## REVISION The implementation number of CURRENT (read: number of bugs fixed...)
## AGE The number of interfaces implemented, minus one.
## The library supports all interfaces between CURRENT − AGE and CURRENT.
##
## If you have 
## not changed the interface (bug fixes)         CURRENT : REVISION+1 : AGE
## augmented the interface (new functions)       CURRENT+1 : 0 : AGE+1
## broken old interface (e.g. removed functions) CURRENT+1 : 0 : 0


AM_CPPFLAGS = @CPP_FLAGS@ -I$(top_builddir)/lib -I$(top_srcdir)/lib -I$(top_builddir) -I$(top_srcdir)
AM_CFLAGS =   @C_FLAGS@
AM_LDFLAGS =  @LD_FLAGS@


MMCPU_VERSIONING = 0:0:0 

lib_LTLIBRARIES = libmmcpu.la

libmmcpu_la_SOURCES = cpu.c
libmmcpu_la_LDFLAGS = -version-info $(MMCPU_VERSIONING)

include_HEADERS = mmcpu/cpu.h mmcpu/mask.h
