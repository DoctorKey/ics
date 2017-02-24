#include "cpu/exec/helper.h"
/* for instruction encoding overloading */

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(cdq)
{
	if(cpu.eax < 0)
		cpu.edx = 0xffffffff;
	else
		cpu.edx = 0;

	print_asm("cdq");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
