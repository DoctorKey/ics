#include "cpu/exec/helper.h"
/*
#define DATA_BYTE 1
#include "leave-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "leave-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "leave-template.h"
#undef DATA_BYTE
*/
/* for instruction encoding overloading */
#define DATA_BYTE 1
#include "cpu/exec/template-start.h"
make_helper(cmps_b)
{
	int dest = swaddr_read(cpu.esi,1);
	int src  = swaddr_read(cpu.edi,1);
	int result = dest - src;
	int max = 0x7f;
	int min = 0x80;

	if(cpu.EFLAGS.DF == 0){
		cpu.esi += 1;
		cpu.edi += 1;
	}else{
		cpu.esi -= 1;
		cpu.edi -= 1;
	}
	if(dest < src)
		cpu.EFLAGS.CF = 1;
	else
		cpu.EFLAGS.CF = 0;
	if(((src < 0) && (dest > (max + src))) || ((src > 0) && (dest < (min + src)))){
		cpu.EFLAGS.OF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
	}
	uint8_t pf;
	pf = result & 0xff;
	pf ^= pf >> 4;
	pf ^= pf >> 2;
	pf ^= pf >> 1;
	cpu.EFLAGS.PF = pf;
	if(result == 0)
		cpu.EFLAGS.ZF = 1;
	else
		cpu.EFLAGS.ZF = 0;

	cpu.EFLAGS.SF = result >> 7;
	
	print_asm("cmp_b");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
#define DATA_BYTE 2
#include "cpu/exec/template-start.h"
make_helper(cmps_v)
{
	int dest,src,result,max,min,size;
	if(ops_decoded.is_operand_size_16 == true){
		size = 2;
		max = 0x7fff;
		min = 0x8000;
	}else{
		size = 4;
		max = 0x7fffffff;
		min = 0x80000000;
	}

	dest = swaddr_read(cpu.esi,size);
	src  = swaddr_read(cpu.edi,size);
	result = dest - src;
	if(cpu.EFLAGS.DF == 0){
		cpu.esi += size;
		cpu.edi += size;
	}else{
		cpu.esi -= size;
		cpu.edi -= size;
	}
	cpu.EFLAGS.SF = result >> (8 * size - 1);

	if(dest < src)
		cpu.EFLAGS.CF = 1;
	else
		cpu.EFLAGS.CF = 0;
	if(((src < 0) && (dest > (max + src))) || ((src > 0) && (dest < (min + src)))){
		cpu.EFLAGS.OF = 1;
	}else{
		cpu.EFLAGS.OF = 0;
	}
	uint8_t pf;
	pf = result & 0xff;
	pf ^= pf >> 4;
	pf ^= pf >> 2;
	pf ^= pf >> 1;
	cpu.EFLAGS.PF = pf;
	if(result == 0)
		cpu.EFLAGS.ZF = 1;
	else
		cpu.EFLAGS.ZF = 0;

	print_asm("cmps_v");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
/*
#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(cmps)
{
	uint32_t source_index,destination_index;
	source_index = cpu.esi;
	destination_index = cpu.edi;
	if(source_index == destination_index){
		cpu.esi += 4;
		cpu.edi += 4;
	}else{
		cpu.esi -= 4;
		cpu.edi -= 4;
	}

	print_asm("cmps");
	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE
*/
