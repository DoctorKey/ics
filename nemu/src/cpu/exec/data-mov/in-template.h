#include "cpu/exec/template-start.h"

#define instr in
uint32_t pio_read(uint32_t,int);
/*
static void do_execute() {
	cpu.eax = pio_read(op_src->val, 4);
//	OPERAND_W(op_dest, pio_read(op_src-val, 4));
	print_asm_template1();
}
*/
make_helper(concat(in_i2a_, SUFFIX)) {
	int len = decode_si_b(eip + 1);
	cpu.eax = pio_read(op_src->val, DATA_BYTE);
	print_asm_template1();
	return len + 1;
}

make_helper(concat(in_d2a_, SUFFIX)) {
	cpu.eax = pio_read(cpu.edx, DATA_BYTE);

	print_asm("in" str(SUFFIX) " %%%s,%%%s",REG_NAME(R_EDX), REG_NAME(R_EAX));
	return 1;
}

#include "cpu/exec/template-end.h"
