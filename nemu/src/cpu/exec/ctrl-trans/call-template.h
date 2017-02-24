#include "cpu/exec/template-start.h"

#define instr call
static void do_execute () {

	if(op_src->type == OP_TYPE_IMM){
		cpu.esp = cpu.esp - DATA_BYTE;
		MEM_W(cpu.esp,cpu.eip + DATA_BYTE + 1);	
		cpu.eip = cpu.eip + op_src->val;
	}
	if(op_src->type == OP_TYPE_REG || op_src->type == OP_TYPE_MEM){
		cpu.esp = cpu.esp - DATA_BYTE;
		if(op_src->type == OP_TYPE_REG){
			MEM_W(cpu.esp,cpu.eip + 2);	
		}else{
			MEM_W(cpu.esp,cpu.eip + DATA_BYTE + 1);	
		}
		cpu.eip = op_src->val - 2;//len=2 minus len to exec at eip
		if(DATA_BYTE == 2)
			cpu.eip &= 0xffff;
	}
	print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"
