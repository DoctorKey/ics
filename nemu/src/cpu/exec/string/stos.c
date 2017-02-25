#include "cpu/exec/helper.h"
/* for instruction encoding overloading */
#define DATA_BYTE 1
#include "cpu/exec/template-start.h"
make_helper(stos_b)
{
	swaddr_write(cpu.edi,1, R_ES, cpu.gpr[R_EAX]._8[0]);
	if(cpu.EFLAGS.DF == 0)
		cpu.edi = cpu.edi + 1;
	else
		cpu.edi = cpu.edi - 1;
		
	print_asm("stos_v");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
#define DATA_BYTE 2
#include "cpu/exec/template-start.h"
make_helper(stos_v)
{
	if(ops_decoded.is_operand_size_16 == true){
		swaddr_write(cpu.edi,2, R_ES, cpu.gpr[R_EAX]._16);
		if(cpu.EFLAGS.DF == 0)
			cpu.edi = cpu.edi + 2;
		else
			cpu.edi = cpu.edi - 2;
	}else{
		swaddr_write(cpu.edi,4, R_ES, cpu.gpr[R_EAX]._32);
		if(cpu.EFLAGS.DF == 0)
			cpu.edi = cpu.edi + 4;
		else
			cpu.edi = cpu.edi - 4;
	}

	print_asm("stos_v");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
/*
#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(stos)
{
	MEM_W(cpu.edi,cpu.eax);
	cpu.edi = cpu.edi + 4;

	print_asm("stos");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
*/
