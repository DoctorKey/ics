#include "cpu/exec/helper.h"
/* for instruction encoding overloading */

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(lgdt)
{
	uint32_t lnaddr = instr_fetch(eip + 2, 4);
	/* important!! instr is lnaddr not base and limit */
	/* use lnaddr_read to get base and limit */
	cpu.GDTR.limit = lnaddr_read(lnaddr, 2);
	if(ops_decoded.is_operand_size_16 == true){
		cpu.GDTR.base = lnaddr_read(lnaddr + 2, 4) & 0xffffff;
	}else{
		cpu.GDTR.base = lnaddr_read(lnaddr + 2, 4);
	}

	print_asm("lgdt_l 0x%x:0x%x", cpu.GDTR.limit, cpu.GDTR.base);
	return 6;

}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
