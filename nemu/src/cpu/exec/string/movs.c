#include "cpu/exec/helper.h"
/* for instruction encoding overloading */

#define DATA_BYTE 2
#include "cpu/exec/template-start.h"
make_helper(movs_b)
{
	swaddr_write(cpu.edi, 1, R_ES, swaddr_read(cpu.esi, 1, R_DS));
	if(cpu.EFLAGS.DF == 0){
		cpu.edi += 1;
		cpu.esi += 1;
	}else{
		cpu.edi -= 1;
		cpu.esi -= 1;
	}
	print_asm("movs_b");
	return 1;
}
make_helper(movs_v)
{
	int size;
	if(ops_decoded.is_operand_size_16 == true){
		size = 2;
	}else{
		size = 4;
	}
	swaddr_write(cpu.edi,size, R_ES, swaddr_read(cpu.esi,size, R_DS));
	if(cpu.EFLAGS.DF == 0){
		cpu.edi += size;
		cpu.esi += size;
	}else{
		cpu.edi -= size;
		cpu.esi -= size;
	}

	print_asm("movs_v");
	return 1;
}

#include "cpu/exec/template-end.h"
#undef DATA_BYTE
