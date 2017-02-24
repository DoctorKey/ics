#include "cpu/exec/template-start.h"

#define instr inc

static void do_execute () {
	DATA_TYPE result = op_src->val + 1;
	OPERAND_W(op_src, result);

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
	if(op_src->val == DATA_MAX){
		cpu.EFLAGS.OF = 1;
		cpu.EFLAGS.CF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
		cpu.EFLAGS.CF = 0;
	}
	cpu.EFLAGS.SF = result >> (8 * DATA_BYTE - 1);
/*
#if DATA_BYTE == 1
	if(op_src->val == 0xff){
		cpu.EFLAGS.OF = 1;
		cpu.EFLAGS.CF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
		cpu.EFLAGS.CF = 0;
	}
	cpu.EFLAGS.SF = result >> 7;
#elif DATA_BYTE == 2
	if(op_src->val == 0xffff){
		cpu.EFLAGS.OF = 1;
		cpu.EFLAGS.CF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
		cpu.EFLAGS.CF = 0;
	}
	cpu.EFLAGS.SF = result >> 15;
#elif DATA_BYTE == 4
	if(op_src->val == 0xffffffff){
		cpu.EFLAGS.OF = 1;
		cpu.EFLAGS.CF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
		cpu.EFLAGS.CF = 0;
	}
	cpu.EFLAGS.SF = result >> 31;
#endif
*/
	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
