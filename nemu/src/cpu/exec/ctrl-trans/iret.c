#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "iret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "iret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "iret-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */


make_helper(iret)
{
	if(ops_decoded.is_operand_size_16 == true){
		cpu.eip = swaddr_read(cpu.esp,2, R_SS);
		cpu.esp = cpu.esp + 2;
		cpu.cs.val = swaddr_read(cpu.esp,2, R_SS);
		cpu.esp = cpu.esp + 2;
		cpu.EFLAGS.val = swaddr_read(cpu.esp,2, R_SS);
		cpu.esp = cpu.esp + 2;
	}else{
		cpu.eip = swaddr_read(cpu.esp,4, R_SS);
		cpu.esp = cpu.esp + 4;
		cpu.cs.val = swaddr_read(cpu.esp,4, R_SS);
		cpu.esp = cpu.esp + 4;
		cpu.EFLAGS.val = swaddr_read(cpu.esp,4, R_SS);
		cpu.esp = cpu.esp + 4;
	}
	print_asm("iret");
	return 0;
}
