#include "cpu/exec/template-start.h"

#define instr jmp
static void do_execute () {

	if(op_src->type == OP_TYPE_IMM){
		cpu.eip += op_src->val;
	}else if(op_src->type == OP_TYPE_REG){
		cpu.eip = op_src->val - 2;
	}else if(op_src->type == OP_TYPE_MEM){
		cpu.eip = op_src->val - 7;//7 sometimes right
	}else{
		printf("no jmp type!!\n");
	}
	
	print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"
