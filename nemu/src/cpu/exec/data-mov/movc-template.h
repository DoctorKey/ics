#include "cpu/exec/template-start.h"

make_helper(movc_r2c_l){
	/* eip is pointing to the opcode */
	/* important!! rm mode */
	//int len = decode_rm_l(eip + 1);
	int len = decode_rm2r_l(eip + 1);
	if(op_dest->reg == 0){
		cpu.cr0.val = op_src->val;
	}else if(op_dest->reg ==3){
		cpu.cr3.val = op_src->val;
	}else{
		printf("not cr0 and cr3\n");
	}
	print_asm("mov %%%s,cr%d", REG_NAME(op_src->reg),  op_dest->reg);
	return len + 1;	// "1" for opcode
}
make_helper(movc_c2r_l){
	/* eip is pointing to the opcode */
	/* important!! rm mode */
	int len = decode_r2rm_l(eip + 1);
	if(op_src->reg == 0){
		OPERAND_W(op_dest, cpu.cr0.val);
	}else if(op_src->reg ==3){
		OPERAND_W(op_dest, cpu.cr3.val);
	}else{
		printf("not cr0 and cr3\n");
	}
	print_asm("mov cr%d,%%%s",  op_src->reg, REG_NAME(op_dest->reg));
	//OPERAND_W(op_src, cpu.cr0.val);
	return len + 1;	// "1" for opcode
}

#include "cpu/exec/template-end.h"
