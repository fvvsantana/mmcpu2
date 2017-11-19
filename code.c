/* code-c - Student's code for mmcpu

   Copyright 2017  Monaco F. J.   <monaco@icmc.usp.br>

   This file is part of Muticlycle Mips CPU (MMCPU)

   MMCPU is free software: you can redistribute it and/or modify
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


/* After you have implemented your functions, you may safely remove these lines. */
#include <stdio.h>
#include <stdlib.h>
#include "mask.h"

#define max_int 0xffffffff
#define opc_rtype 0x00
#define opc_jmp 0x02
#define opc_beq 0x04
#define opc_lw 0x23
#define opc_sw 0x2b


#define not_implemented() fprintf(stderr, "Not implemented\n"); exit(EXIT_FAILURE)

/* Students, you are required to implemented the functions bellow.
   Please, refere to cpu.h for further information. */



int alu( int a, int b, char alu_op, int *result_alu, char *zero, char *overflow)
{
    char operation = alu_op & separa_controle_ula;

    //to treat overflow
    long int total;
    long int la = a;
    long int lb = b;

    switch(operation){
        case ativa_soma:
            total = la + lb;
            *overflow = total > max_int;
            *result_alu = a + b;
            break;

        case ativa_subtracao:
            total = la - lb;
            *overflow = total > max_int;
            *result_alu = a - b;
            break;

        case ativa_and:
            *result_alu = a & b;
            *overflow = 0;
            break;

        case ativa_or:
            *result_alu = a | b;
            *overflow = 0;
            break;

        case ativa_slt:
            *result_alu = a < b;
            *overflow = 0;
            break;

        case ativa_nor:
            *result_alu = ~(a | b);
            *overflow = 0;
            break;
    }

    //update zero value
    *zero = !(result_alu);

    return 0;
}

//dispatch table 1
char dispatchRom1(char opc){
    switch(opc){
        case opc_rtype:
            return 6;

        case opc_jmp:
            return 9;

        case opc_beq:
            return 8;

        case opc_lw:
            return 2;

        case opc_sw:
            return 2;
    }

}

//dispatch table 2
char dispatchRom2(char opc){
    switch(opc){
        case opc_lw:
            return 3;

        case opc_sw:
            return 5;
    }

}

void control_unit(int IR, short int *sc)
{
    static char state = 0;
    static char addrCtrl = 0;

    //address select logic (set current state)
    switch(addrCtrl){
        case 0:
            state = 0;
            break;

        case 1:
            state = dispatchRom1(((IR & separa_cop) >> 26));
            break;

        case 2:
            state = dispatchRom2(((IR & separa_cop) >> 26));
            break;

        case 3:
            state++;
            break;

    }

    //clean sc
    *sc = 0;

    //update addrCtrl and control signals for the current state
    switch(state){
        case 0:
            *sc |= (ativa_MemRead | 
                    ativa_IRWrite |
                    ativa_ALUSrcB0 |
                    ativa_PCWrite
                    );

            addrCtrl = 3;
            break;

        case 1:
            *sc |= (ativa_ALUSrcB1 | 
                    ativa_ALUSrcB0
                    );
            addrCtrl = 1;
            break;

        case 2:
            *sc |= (ativa_ALUSrcA | 
                    ativa_ALUSrcB1
                    );
            addrCtrl = 2;
            break;

        case 3:
            *sc |= (ativa_MemRead | 
                    ativa_IorD
                    );
            addrCtrl = 3;
            break;

        case 4:
            *sc |= (ativa_RegWrite | 
                    ativa_MemtoReg
                    );
            addrCtrl = 0;
            break;

        case 5:
            *sc |= (ativa_MemWrite | 
                    ativa_IorD
                    );
            addrCtrl = 0;
            break;

        case 6:
            *sc |= (ativa_ALUSrcA | 
                    ativa_ALUOp1
                    );
            addrCtrl = 3;
            break;

        case 7:
            *sc |= (ativa_RegDst | 
                    ativa_RegWrite
                    );
            addrCtrl = 0;
            break;

        case 8:
            *sc |= (ativa_ALUSrcA| 
                    ativa_ALUOp0 |
                    ativa_PCWriteCond |
                    ativa_PCSource0 
                    );
            addrCtrl = 0;
            break;

        case 9:
            *sc |= (ativa_PCWrite | 
                    ativa_PCSource1
                    );
            addrCtrl = 0;
            break;

    }


    not_implemented();

}


void instruction_fetch(short int sc, int PC, int ALUOUT, int IR, int* PCnew, int* IRnew, int* MDRnew)
{
}


void decode_register(short int sc, int IR, int PC, int A, int B, int *Anew, int *Bnew, int *ALUOUTnew)
{
}


void exec_calc_end_branch(short int sc, int A, int B, int IR, int PC, int ALUOUT, int *ALUOUTnew, int *PCnew)
{
}


void write_r_access_memory(short int sc, int IR, int MDR, int AMUOUT, int PC, int *MDRnew, int *IRnew)
{
}


void write_ref_mem(short int sc, int IR, int MDR, int ALUOUT)
{
}


