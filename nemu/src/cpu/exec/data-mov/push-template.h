#include "cpu/exec/template-start.h"

#define instr push

static void do_execute() {
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp,op_src->val);	
	print_asm_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif
/*
make_helper(concat(push_r_, SUFFIX)) {
	uint8_t op = instr_fetch(eip, 1);
	cpu.esp = cpu.esp - 4;
	MEM_W(cpu.esp,REG(op & 0x0f));	

	print_asm("push" str(SUFFIX) " %%%s,0x%x", REG_NAME(op & 0x0f), cpu.esp);
	return 1;
}
*/
#include "cpu/exec/template-end.h"
