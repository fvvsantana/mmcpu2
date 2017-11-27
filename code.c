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
#include "cpu.h"

#define max_int 0xffffffff
#define opc_rtype 0x00
#define opc_jmp 0x02
#define opc_beq 0x04
#define opc_lw 0x23
#define opc_sw 0x2b

#define func_add 0x20
#define func_sub 0x22
#define func_and 0x24
#define func_or 0x25
#define func_slt 0x2a
#define func_nor 0x27


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
            if(overflow) *overflow = total > max_int;
            if(result_alu) *result_alu = a + b;
            break;

        case ativa_subtracao:
            total = la - lb;
            if(overflow) *overflow = total > max_int;
            if(result_alu) *result_alu = a - b;
            break;

        case ativa_and:
            if(result_alu) *result_alu = a & b;
            if(overflow) *overflow = 0;
            break;

        case ativa_or:
            if(result_alu) *result_alu = a | b;
            if(overflow) *overflow = 0;
            break;

        case ativa_slt:
            if(result_alu) *result_alu = a < b;
            if(overflow) *overflow = 0;
            break;

        case ativa_nor:
            if(result_alu) *result_alu = ~(a | b);
            if(overflow) *overflow = 0;
            break;
    }

    //update zero value
    if(zero) *zero = !(*result_alu);

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

    //not_implemented();

}

/*alu_control: according to the control signals aluop0 and aluop1 and
 * according to the function code, alu_control put in the output the
 * operation code that is meant to be passed to the ula.  */
void alu_control(char aluop1, char aluop0, char cfunct, char* output){
    if(aluop1 == 0 && aluop0 == 0){
        *output = ativa_soma;
    }else if(aluop1 == 0 && aluop0 == 1){
        *output = ativa_subtracao;
    }else if(aluop1 == 1){
        char last4Bits = cfunct & 0x0f; // 0000 1111

        if(last4Bits == 2){
            *output = ativa_subtracao;
        }else if(last4Bits == 10){
            *output = ativa_slt;
        }else if(aluop0 == 0){
            if(last4Bits == 0){
                *output = ativa_soma;
            }else if(last4Bits == 4){
                *output = ativa_and;
            }else if(last4Bits == 5){
                *output = ativa_or;
            }else if(last4Bits == 7){
                *output = ativa_nor;
            }
        }
    }
}

void instruction_fetch(short int sc, int PC, int ALUOUT, int IR, int* PCnew, int* IRnew, int* MDRnew)
{

    //verify if the control signals allow the operation to be done
    if(
        ((sc & separa_IorD) == 0) &&
        ((sc & separa_MemRead) == ativa_MemRead) &&
        ((sc & separa_IRWrite) == ativa_IRWrite)
      ){
        //instruction fetch
        *IRnew = memory[PC];
    }

    //verify if the control signals allow the operation to be done
    if(
        ((sc & separa_ALUSrcA) == 0) &&
        ((sc & separa_ALUSrcB1) == 0) &&
        ((sc & separa_ALUSrcB0) == ativa_ALUSrcB0) &&
        ((sc & separa_ALUOp1) == 0) &&
        ((sc & separa_ALUOp0) == 0) &&
        ((sc & separa_PCSource1) == 0) &&
        ((sc & separa_PCSource0) == 0) &&
        ((sc & separa_PCWrite) == ativa_PCWrite)
      ){
        //get alu control output
        char aluControlOutput;
        alu_control(0, 0, IR & separa_cfuncao, &aluControlOutput);

        //update PC (*PCnew = PC + 1)
        alu(PC, 1, aluControlOutput, PCnew, NULL, NULL);
    }

    //update mdr
    *MDRnew = *IRnew;
}


void decode_register(short int sc, int IR, int PC, int A, int B, int *Anew, int *Bnew, int *ALUOUTnew)
{
    //*Anew = reg[IR[25-21]]
    *Anew = reg[(IR & separa_rs) >> 21];
    *Bnew = reg[(IR & separa_rt) >> 16];

    //verify if the control signals allow the operation to be done
    if(
        ((sc & separa_ALUSrcA) == 0) &&
        ((sc & separa_ALUSrcB1) == ativa_ALUSrcB1) &&
        ((sc & separa_ALUSrcB0) == ativa_ALUSrcB0) &&
        ((sc & separa_ALUOp1) == 0) &&
        ((sc & separa_ALUOp0) == 0)
      ){
        //get alu control output
        char aluControlOutput;
        alu_control(0, 0, IR & separa_cfuncao, &aluControlOutput);

        //*ALUOUTnew = PC + ext(IR[15-0])
        alu(PC, (IR & separa_imediato), aluControlOutput, ALUOUTnew, NULL, NULL);
    }

}


void exec_calc_end_branch(short int sc, int A, int B, int IR, int PC, int ALUOUT, int *ALUOUTnew, int *PCnew)
{
    //verify if the control signals allow the operation to be done
    //lw sw
    if(
        ((sc & separa_ALUSrcA) == ativa_ALUSrcA) &&
        ((sc & separa_ALUSrcB1) == ativa_ALUSrcB1) &&
        ((sc & separa_ALUSrcB0) == 0) &&
        ((sc & separa_ALUOp1) == 0) &&
        ((sc & separa_ALUOp0) == 0)
      ){
        //get alu control output
        char aluControlOutput;
        alu_control(0, 0, IR & separa_cfuncao, &aluControlOutput);

        //*ALUOUTnew = A + ext(IR[15-0])
        alu(A, (IR & separa_imediato), aluControlOutput, ALUOUTnew, NULL, NULL);
    }

    //r-type
    if(
        ((sc & separa_ALUSrcA) == ativa_ALUSrcA) &&
        ((sc & separa_ALUSrcB1) == 0) &&
        ((sc & separa_ALUSrcB0) == 0) &&
        ((sc & separa_ALUOp1) == ativa_ALUOp1) &&
        ((sc & separa_ALUOp0) == 0)
      ){
        //get alu control output
        char aluControlOutput;
        alu_control(1, 0, IR & separa_cfuncao, &aluControlOutput);

        //*ALUOUTnew = A op B
        alu(A, B, aluControlOutput, ALUOUTnew, NULL, NULL);

    }

    //beq
    if(
        ((sc & separa_ALUSrcA) == ativa_ALUSrcA) &&
        ((sc & separa_ALUSrcB1) == 0) &&
        ((sc & separa_ALUSrcB0) == 0) &&
        ((sc & separa_ALUOp1) == 0) &&
        ((sc & separa_ALUOp0) == ativa_ALUOp0) &&
        ((sc & separa_PCWriteCond) == ativa_PCWriteCond) &&
        ((sc & separa_PCSource1) == 0) &&
        ((sc & separa_PCSource0) == ativa_PCSource0)
      ){
        //get alu control output
        char aluControlOutput;
        alu_control(0, 1, IR & separa_cfuncao, &aluControlOutput);

        //if(A==B) PCnew = ALUOUT
        char zero;
        alu(A, B, aluControlOutput, ALUOUTnew, &zero, NULL);
        if(zero){
            *PCnew = ALUOUT;
        }
    }

    //jump
    if(
        ((sc & separa_PCWrite) == ativa_PCWrite) &&
        ((sc & separa_PCSource1) == ativa_PCSource1) &&
        ((sc & separa_PCSource0) == 0)
      ){
        //*PCnew = PC[31-28] || (IR[25-0] << 2)
        (*PCnew) = IR & separa_imediato;
    }


}


void write_r_access_memory(short int sc, int B, int IR, int MDR, int ALUOUT, int PC, int *MDRnew, int *IRnew)
{
    //verify if the control signals allow the operation to be done
    //lw
    if(
        ((sc & separa_MemRead) == ativa_MemRead) &&
        ((sc & separa_IorD) == ativa_IorD)      
        ){

        *MDRnew = memory[ALUOUT];
    }

    //sw
    if(
        ((sc & separa_MemWrite) == ativa_MemWrite) &&
        ((sc & separa_IorD) == ativa_IorD)      
        ){

        memory[ALUOUT] = B;
    }

    //r-type
    if(
        ((sc & separa_RegDst) == ativa_RegDst) &&
        ((sc & separa_RegWrite) == ativa_RegWrite) &&
        ((sc & separa_MemtoReg) == 0)      
        ){

        reg[(IR & separa_rd) >> 11] = ALUOUT;
    }

}


void write_ref_mem(short int sc, int IR, int MDR, int ALUOUT)
{
    //verify if the control signals allow the operation to be done
    //lw
    if(
        ((sc & separa_RegDst) == 0) &&
        ((sc & separa_RegWrite) == ativa_RegWrite) &&
        ((sc & separa_MemtoReg) == ativa_MemtoReg)      
        ){

        reg[(IR & separa_rt) >> 16] = MDR;
    }

    not_implemented();
}


