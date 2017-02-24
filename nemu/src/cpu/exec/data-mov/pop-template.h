#include "cpu/exec/template-start.h"

#define instr pop

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
	switch(op_src->type){
	case OP_TYPE_REG:
		cpu.gpr[op_src->reg]._32 = MEM_R(cpu.esp);
		break;
	case OP_TYPE_MEM:
		OPERAND_W(op_src,cpu.esp);	
		break;
	default:
		printf("no pop type!!\n");
	}
	cpu.esp = cpu.esp + DATA_BYTE;

	print_asm_template1();
}

make_instr_helper(rm)
make_instr_helper(r)
#endif
#include "cpu/exec/template-end.h"
