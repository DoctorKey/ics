#include "common.h"
#include "cpu/reg.h"
#include "../../../lib-common/x86-inc/mmu.h"
#include "memory/seg.h"

uint32_t hwaddr_read(hwaddr_t addr, size_t len); 
uint32_t lnaddr_read(lnaddr_t addr, size_t len); 
lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg)
{
	/* run in real mode */
	if(cpu.cr0.protect_enable == 0){
		return addr;
	}

	/* run in protect mode */
	/* TI = 1 check LDT; TI = 0 check GDT */
	if(cpu.seg[sreg].TI == 1){
		printf("not use LDT\n");
		assert(0);
	}
	/* get seg_choose_index */
	uint16_t seg_choose_index = cpu.seg[sreg].INDEX;
	seg_choose_index <<= 3;
	if(seg_choose_index > cpu.GDTR.limit){
		printf("seg_choose_index exceed GDTR_LIM!\n");
		assert(0);
	}
	/* get segdesc */
	uint32_t segdesc_hwaddr = cpu.GDTR.base + seg_choose_index;
	uint32_t temp[2];
	//temp[0] = hwaddr_read(segdesc_hwaddr,4);
	//temp[1] = hwaddr_read(segdesc_hwaddr + 4,4);
	temp[0] = lnaddr_read(segdesc_hwaddr,4);
	temp[1] = lnaddr_read(segdesc_hwaddr + 4,4);
	SegDesc *segdesc = (SegDesc *)temp;

	lnaddr_t base = (segdesc->base_31_24 << 24) + (segdesc->base_23_16 << 16) + (segdesc->base_15_0);
	return base + addr;
}
