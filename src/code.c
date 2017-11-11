/* code-c - Student's code for mmcpu

   Copyright 2017  [Your Name]   [<your email>]

   This file is part of [Your Project]

   [Your Project] is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <mmcpu/cpu.h>

/* Students, you are required to implemented the functions bellow.
   Please, refere to cpu.h for further information. */



int alu( int a, int b, char alu_op, int *result_alu, char *zero, char *overflow)
{
  return 0;
}


void control_unit(int IR, short int *sc)
{
  not_implemented();
}


void instruction_fetch(short int sc, int PC, int ALUOUT, int IR,
		       int* PCnew, int* IRnew, int* MDRnew)
{
  not_implemented();
}


void decode_register(short int sc, int IR, int PC, int A, int B,
		     int *Anew, int *Bnew, int *ALUOUTnew)
{
  not_implemented();
}


void exec_calc_end_branch(short int sc, int A, int B, int IR, int PC,
			  int ALUOUT, int *ALUOUTnew, int *PCnew)
{
  not_implemented();
}


void write_r_access_memory(short int sc, int IR, int MDR, int AMUOUT,
			   int PC, int *MDRnew, int *IRnew)
{
  not_implemented();
}


void write_ref_mem(short int sc, int IR, int MDR, int ALUOUT)
{
  not_implemented();
}


