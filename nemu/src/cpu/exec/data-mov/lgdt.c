#include "cpu/exec/helper.h"
/* for instruction encoding overloading */

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(lgdt)
{
	int len = decode_rm_l(eip + 1);
	uint32_t lnaddr = op_src->addr;
	/* important!! instr is lnaddr not base and limit */
	/* use lnaddr_read to get base and limit */
	cpu.GDTR.limit = lnaddr_read(lnaddr, 2);
	if(ops_decoded.is_operand_size_16 == true){
		cpu.GDTR.base = lnaddr_read(lnaddr + 2, 4) & 0xffffff;
	}else{
		cpu.GDTR.base = lnaddr_read(lnaddr + 2, 4);
	}

	print_asm("lgdt_l 0x%x:0x%x", cpu.GDTR.limit, cpu.GDTR.base);
	return len + 1;
}
make_helper(lidt)
{
	int len = decode_rm_l(eip + 1);
	uint32_t lnaddr = op_src->addr;
	/* important!! instr is lnaddr not base and limit */
	/* use lnaddr_read to get base and limit */
	cpu.IDTR.limit = lnaddr_read(lnaddr, 2);
	if(ops_decoded.is_operand_size_16 == true){
		cpu.IDTR.base = lnaddr_read(lnaddr + 2, 4) & 0xffffff;
	}else{
		cpu.IDTR.base = lnaddr_read(lnaddr + 2, 4);
	}

	print_asm("lidt_l 0x%x:0x%x", cpu.IDTR.limit, cpu.IDTR.base);
	return len + 1;
}

#include "cpu/exec/template-end.h"
#undef DATA_BYTE
