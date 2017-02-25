#include "cpu/exec/template-start.h"

#define instr mov

static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, R_DS, REG(R_EAX));

	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr, R_DS);

	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}
#if DATA_BYTE == 2
make_helper(concat(mov_rm2sr_, SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	cpu.seg[op_dest->reg].val = op_src->val;

	printf("sr=%d,value=%x\n",op_dest->reg,op_src->val);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(mov_sr2rm_, SUFFIX)) {
	int len = concat(decode_r2rm_, SUFFIX)(eip + 1);
	OPERAND_W(op_dest, cpu.seg[op_src->reg].val);

	printf("sr=%d,value=%x\n",op_src->reg,op_src->val);
	print_asm_template2();
	return len + 1;
}
#endif
#include "cpu/exec/template-end.h"
