#include "cpu/exec/helper.h"
/* for instruction encoding overloading */

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(leave)
{
	cpu.esp = cpu.ebp;
	cpu.ebp = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + 4;

	print_asm("leave");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
