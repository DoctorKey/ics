#include "cpu/exec/template-start.h"

#define instr sub
static void do_execute () {
	DATA_TYPE result = op_dest->val - op_src->val;
	OPERAND_W(op_dest, result);
	int dest = op_dest->val;
	int src = op_src->val;
	int max = DATA_MAX;
	int min = DATA_MIN;

	if(op_dest->val < op_src->val)
		cpu.EFLAGS.CF = 1;
	else
		cpu.EFLAGS.CF = 0;
	if(((src < 0) && (dest > (max + src))) || ((src > 0) && (dest < (min + src)))){
		cpu.EFLAGS.OF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
	}
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
/*
#if DATA_BYTE == 1
	cpu.EFLAGS.SF = result >> 7;
#elif DATA_BYTE == 2
	cpu.EFLAGS.SF = result >> 15;
#elif DATA_BYTE == 4
	cpu.EFLAGS.SF = result >> 31;
#endif
*/	
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
