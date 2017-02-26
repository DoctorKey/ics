#include "cpu/exec/template-start.h"

#define instr jmp
static void do_execute () {

	if(op_src->type == OP_TYPE_IMM){
		cpu.eip += op_src->val;
	}else if(op_src->type == OP_TYPE_REG){
		cpu.eip = op_src->val - 2;
	}else if(op_src->type == OP_TYPE_MEM){
		cpu.eip = op_src->val - 7;//7 sometimes right
	}else{
		printf("no jmp type!!\n");
	}
	
	print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)
#if DATA_BYTE == 4
make_helper(ljmp) {
	/* important!! the order of eip and cs ptr16:32*/
	cpu.eip = instr_fetch(eip + 1, 4);
	cpu.cs.val = instr_fetch(eip + 5, 2);

	print_asm("ljmp 0x%x:0x%x", cpu.cs.val, cpu.eip);
	return 0;
}
#endif
#include "cpu/exec/template-end.h"
