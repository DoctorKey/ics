#include "cpu/reg.h"
#include "../../../lib-common/x86-inc/mmu.h"
#include "memory/page.h"
#include "memory/tlb.h"
static bool debug = 0;
extern uint32_t hwaddr_read(hwaddr_t, size_t);
TLB tlb;
hwaddr_t page_translate(lnaddr_t addr)
{
	/* enable page when PE == 1 && PG == 1 */
	if(!(cpu.cr0.protect_enable == 1 && cpu.cr0.paging == 1)){
		return addr;
	}

	bool state = false;
	hwaddr_t offset = addr & 0xfff;
	hwaddr_t phy_page = tlb.check(&tlb, addr, &state);
	if(state == true){
		if(debug == 1){
			printf("hit the tlb\n");
			printf("phy_addr:\t0x%08x\n", phy_page + offset);
		}
		return phy_page + offset;
	}
	hwaddr_t dir = (addr >> 22) & 0x3ff;
	hwaddr_t page = (addr >> 12) & 0x3ff;
	if(debug == 1){
		printf("dir:0x%x  page:0x%x  offset:0x%x\n", dir, page, offset);
	}
	/* get page directory item */
	hwaddr_t dir_item_addr = (cpu.cr3.page_directory_base << 12) + (dir << 2);
	PDE dir_item = (PDE)hwaddr_read(dir_item_addr, 4);
	if((dir_item.val & 0xf) != 7){
		printf("page fault!\n");
		printf("cr3 = 0x%08x\n", cpu.cr3.val);
		printf("addr = 0x%08x\n", addr);
		if(debug == 1)
			return 0;
		else
			assert(0);
	}
	if(debug == 1){
		printf("dir_addr:\t0x%08x dir_item:\t0x%08x\n", dir_item_addr, dir_item.val);
	}

	/* get page table item */
	hwaddr_t table_item_addr = (dir_item.page_frame << 12) + (page << 2);
	PTE table_item = (PTE)hwaddr_read(table_item_addr, 4);
	if((table_item.val & 0xf) != 7){
		printf("page fault!\n");
		printf("cr3 = 0x%08x\n", cpu.cr3.val);
		printf("addr = 0x%08x\n", addr);
		if(debug == 1)
			return 0;
		else
			assert(0);
	}
	if(debug == 1){
		printf("table_addr:\t0x%08x table_item:\t0x%08x\n", table_item_addr, table_item.val);
	}

	/* get physical addr */
	hwaddr_t phy_addr = (table_item.page_frame << 12) + offset;
	if(debug == 1){
		printf("phy_addr:\t0x%08x\n", phy_addr);
	}
	tlb.write(&tlb, addr, phy_addr);
	return phy_addr;
}
extern void page_test(lnaddr_t addr)
{
	debug = 1;
	hwaddr_t hwaddr = page_translate(addr);
	printf("page addr-->physical addr: 0x%08x --> 0x%08x\n",addr, hwaddr);
	debug = 0;
}
