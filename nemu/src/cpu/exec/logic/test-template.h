#include "cpu/exec/template-start.h"

#define instr test

static void do_execute () {
	DATA_TYPE result = op_dest->val & op_src->val;

	uint8_t pf;
	pf = result & 0xff;
	pf ^= pf >> 4;
	pf ^= pf >> 2;
	pf ^= pf >> 1;
	cpu.EFLAGS.PF = pf;
	if(result == 0)
		cpu.EFLAGS.ZF = 1;
	else
		cpu.EFLAGS.ZF = 0;
	cpu.EFLAGS.SF = result >> (8 * DATA_BYTE - 1);
	cpu.EFLAGS.CF = 0;
	cpu.EFLAGS.OF = 0;

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
