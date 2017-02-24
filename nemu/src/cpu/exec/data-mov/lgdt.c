#include "cpu/exec/helper.h"
/* for instruction encoding overloading */

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(lgdt)
{
	uint16_t m16 = instr_fetch(eip + 1, 2);
	if(ops_decoded.is_operand_size_16 == true){
		cpu.GDTR_LIM = m16;
		uint32_t m24 = instr_fetch(eip + 3, 3);
		cpu.GDTR = m24;
		print_asm("lgdt_w 0x%x:0x%x",m16,m24);
		return 6;
	}else{
		cpu.GDTR_LIM = m16;
		uint32_t m32 = instr_fetch(eip + 3, 4);
		cpu.GDTR = m32;
		print_asm("lgdt_l 0x%x:0x%x",m16,m32);
		return 6;
	}

}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
