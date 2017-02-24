#include "cpu/exec/template-start.h"

#define instr jcc

make_helper(concat(ja_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0 && cpu.EFLAGS.ZF == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jae_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jb_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jbe_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.CF == 1 || cpu.EFLAGS.ZF == 1)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jcxz_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.ecx == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(je_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 1)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jg_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0 && cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jge_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == cpu.EFLAGS.OF)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jl_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jle_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 1 || cpu.EFLAGS.SF != cpu.EFLAGS.OF)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jne_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.ZF == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jno_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.OF == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jnp_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.PF == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jns_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == 0)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jo_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.OF == 1)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(jp_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.PF == 1)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}
make_helper(concat(js_i_,SUFFIX))
{
	int len = concat(decode_si_,SUFFIX)(eip + 1);
	if(cpu.EFLAGS.SF == 1)
		cpu.eip = cpu.eip + op_src->val;
	print_asm_template1();
	return len + 1;
}


#include "cpu/exec/template-end.h"
