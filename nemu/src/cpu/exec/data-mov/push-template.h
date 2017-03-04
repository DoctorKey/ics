#include "cpu/exec/template-start.h"

#define instr push

static void do_execute() {
	/* the stack is 32 bit width .use 4 not DATA_BYTE*/
	cpu.esp = cpu.esp - STACK_SIZE;
	MEM_W(cpu.esp, R_SS, op_src->val);	
	print_asm_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif
#if DATA_BYTE == 4
make_helper(push_cs) {
	cpu.esp = cpu.esp - STACK_SIZE;
	MEM_W(cpu.esp, R_SS, cpu.cs.val);	
	print_asm("push_cs 0x%04x", cpu.cs.val);
	return 0;
}
make_helper(push_ss) {
	cpu.esp = cpu.esp - STACK_SIZE;
	MEM_W(cpu.esp, R_SS, cpu.ss.val);	
	print_asm("push_ss 0x%04x", cpu.ss.val);
	return 0;
}
make_helper(push_ds) {
	cpu.esp = cpu.esp - STACK_SIZE;
	MEM_W(cpu.esp, R_SS, cpu.ds.val);	
	print_asm("push_ds 0x%04x", cpu.ds.val);
	return 0;
}
make_helper(push_es) {
	cpu.esp = cpu.esp - STACK_SIZE;
	MEM_W(cpu.esp, R_SS, cpu.es.val);	
	print_asm("push_es 0x%04x", cpu.es.val);
	return 0;
}
#endif
#include "cpu/exec/template-end.h"
