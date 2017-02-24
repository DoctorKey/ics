#include "cpu/exec/template-start.h"

#define instr setcc

make_helper(concat(seta_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setae_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setb_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setbe_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 1 || cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setc_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(sete_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setg_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setge_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setl_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setle_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 0 || cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setna_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 1 || cpu.EFLAGS.ZF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnae_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnb_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnbe_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnc_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setne_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setng_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 1 || cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnge_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnl_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnle_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setno_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.OF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnp_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.PF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setns_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.SF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setnz_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(seto_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.OF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setp_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.PF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setpe_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.PF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setpo_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.PF == 0)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(sets_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.SF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}
make_helper(concat(setz_rm_,SUFFIX))
{
	int len = decode_rm_b(eip + 1);
	if(cpu.EFLAGS.ZF == 1)
		OPERAND_W(op_src,1);
	else
		OPERAND_W(op_src,0);
	print_asm_template1();
	return len + 1;
}


#include "cpu/exec/template-end.h"
