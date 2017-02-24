#include "cpu/exec/template-start.h"

make_helper(movc_r2c_l){
	/* eip is pointing to the opcode */
	int len = decode_r_l(eip + 1);
	cpu.cr0.val = op_src->val;
	return len + 1;	// "1" for opcode
}
make_helper(movc_c2r_l){
	/* eip is pointing to the opcode */
	int len = decode_r_l(eip + 1);
	OPERAND_W(op_src, cpu.cr0.val);
	return len + 1;	// "1" for opcode
}

#include "cpu/exec/template-end.h"
