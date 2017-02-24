#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	uint32_t result;
#if DATA_BYTE == 1 || DATA_BYTE == 2
	if((op_src->val) >> 7 == 1){
		result = op_src->val | 0xffffff00;
		cpu.gpr[op_dest->reg]._32 = result;
	}else{
		result = op_src->val & 0xff;
		cpu.gpr[op_dest->reg]._32 = result;
//		OPERAND_W(op_dest, op_src->val);
	}
#endif
#if DATA_BYTE == 4
	if((op_src->val) >> 15 == 1){
		result = op_src->val | 0xffff0000;
		cpu.gpr[op_dest->reg]._32 = result;
	}else{
		result = op_src->val & 0xffff;
		cpu.gpr[op_dest->reg]._32 = result;
//		OPERAND_W(op_dest, op_src->val);
	}
#endif
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
