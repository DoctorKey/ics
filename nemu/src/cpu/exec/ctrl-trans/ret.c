#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ret-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper(ret_i_w)
{
	decode_i_w(cpu.eip + 1);
	if(ops_decoded.is_operand_size_16 == true){
		cpu.eip = swaddr_read(cpu.esp,2);
		cpu.esp = cpu.esp + 2;
	}else{
		cpu.eip = swaddr_read(cpu.esp,4);
		cpu.esp = cpu.esp + 4;
	}

	cpu.esp = cpu.esp + op_src->val;
	print_asm("ret 0x%08x",op_src->val);
	return 0;
}
make_helper(ret)
{
	if(ops_decoded.is_operand_size_16 == true){
		cpu.eip = swaddr_read(cpu.esp,2);
		cpu.esp = cpu.esp + 2;
	}else{
		cpu.eip = swaddr_read(cpu.esp,4);
		cpu.esp = cpu.esp + 4;
	}
	print_asm("ret");
	return 0;
}
