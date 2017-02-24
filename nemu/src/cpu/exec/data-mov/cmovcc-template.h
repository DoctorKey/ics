#include "cpu/exec/template-start.h"

#define instr cmovcc

make_helper(concat(cmova_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovae_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovb_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovbe_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1 || cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovc_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmove_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovg_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovge_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovl_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovle_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0 || cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovna_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1 || cpu.EFLAGS.ZF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnae_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnb_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnbe_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnc_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovne_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovng_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 1 || cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnge_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnl_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnle_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovno_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.OF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnp_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.PF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovns_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovnz_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovo_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.OF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovp_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.PF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovpe_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.PF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovpo_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.PF == 0)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovs_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}
make_helper(concat(cmovz_rm2r_,SUFFIX))
{
	int len = concat(decode_rm2r_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 1)
		OPERAND_W(op_dest, op_src->val);
	//else
		//OPERAND_W(op_src,0);
	print_asm_template2();
	return len + 1;
}


#include "cpu/exec/template-end.h"
