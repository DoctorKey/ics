#include "cpu/exec/template-start.h"

#define instr pusha

#if DATA_BYTE == 4
make_helper(pusha) {
	uint32_t temp = cpu.esp;
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.eax);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.ecx);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.edx);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.ebx);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, temp);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.ebp);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.esi);	
	cpu.esp = cpu.esp - DATA_BYTE;
	MEM_W(cpu.esp, R_SS, cpu.edi);	
	print_asm("pusha");
	return 1;
}
#endif
#include "cpu/exec/template-end.h"
