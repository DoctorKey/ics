#include "cpu/exec/template-start.h"

#define instr out
void pio_write(uint32_t,int,uint32_t);
/*
static void do_execute() {
	pio_write(op_src->val, 4, cpu.eax);
//	OPERAND_W(op_dest, pio_read(op_src-val, 4));
	print_asm_template1();
}
*/
make_helper(concat(out_a2i_, SUFFIX)) {
	int len = decode_si_b(eip + 1);
	pio_write(op_src->val, DATA_BYTE, cpu.eax);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(out_a2d_, SUFFIX)) {
	pio_write(cpu.edx, DATA_BYTE, cpu.eax);

	print_asm("out" str(SUFFIX) " %%%s,%%%s",REG_NAME(R_EAX), REG_NAME(R_EDX));
	return 1;
}

#include "cpu/exec/template-end.h"
