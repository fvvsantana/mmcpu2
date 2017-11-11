##   Makefile.am - Automake script for src dir.
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

AM_CPPFLAGS = @CPP_FLAGS@ -I$(top_builddir)/lib -I$(top_srcdir)/lib -I$(top_builddir) -I$(top_srcdir) 
AM_CFLAGS =   @C_FLAGS@
AM_LDFLAGS =  @LD_FLAGS@


## AM_CPPFLAGS = -I$(top_srcdir)/lib

bin_PROGRAMS = mycpu

mycpu_SOURCES = code.c

mycpu_LDADD = ../lib/libmmcpu.la $(LIBOBJS) 

