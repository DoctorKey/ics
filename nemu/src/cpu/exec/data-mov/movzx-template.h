#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
#if DATA_BYTE == 1 || DATA_BYTE == 2
	uint32_t result = op_src->val & 0xff;
	cpu.gpr[op_dest->reg]._32 = result;
#endif
#if DATA_BYTE == 4
	uint32_t result = op_src->val & 0xffff;
	cpu.gpr[op_dest->reg]._32 = result;
#endif

	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
