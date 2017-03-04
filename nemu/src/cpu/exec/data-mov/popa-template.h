#include "cpu/exec/template-start.h"

#define instr popa

#if DATA_BYTE == 4
make_helper(popa) {
	cpu.edi = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.esi = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.ebp = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.ebx = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.edx = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.ecx = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	cpu.eax = MEM_R(cpu.esp, R_SS);
	cpu.esp = cpu.esp + DATA_BYTE;
	print_asm("popa");
	return 1;
}
#endif
#include "cpu/exec/template-end.h"
