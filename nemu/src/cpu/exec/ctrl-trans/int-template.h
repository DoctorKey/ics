#include "cpu/exec/template-start.h"

#define instr int
	void raise_intr(uint8_t);
static void do_execute () {

	if(op_src->type == OP_TYPE_IMM){
		cpu.esp = cpu.esp - DATA_BYTE;
		MEM_W(cpu.esp, R_SS, cpu.EFLAGS.val);	
		cpu.esp = cpu.esp - DATA_BYTE;
		MEM_W(cpu.esp, R_SS, cpu.cs.val);	
		cpu.esp = cpu.esp - DATA_BYTE;
		MEM_W(cpu.esp, R_SS, cpu.eip + 2);	
		print_asm("int %d", op_src->val);
		raise_intr(op_src->val);
	}
	print_asm_template1();
}

make_instr_helper(si)
#include "cpu/exec/template-end.h"
