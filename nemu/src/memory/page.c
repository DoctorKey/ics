#include "cpu/reg.h"
#include "../../../lib-common/x86-inc/mmu.h"
#include "memory/page.h"

extern uint32_t hwaddr_read(hwaddr_t, size_t);
hwaddr_t page_translate(lnaddr_t addr)
{
	/* enable page when PE == 1 && PG == 1 */
	if(!(cpu.cr0.protect_enable == 1 && cpu.cr0.paging == 1)){
		return addr;
	}

	hwaddr_t dir = (addr >> 22) & 0x3ff;
	hwaddr_t page = (addr >> 12) & 0x3ff;
	hwaddr_t offset = addr & 0xfff;
	/* get page directory item */
	hwaddr_t dir_item_addr = (cpu.cr3.page_directory_base << 12) + (dir << 2);
	PDE dir_item = (PDE)hwaddr_read(dir_item_addr, 4);

	/* get page table item */
	hwaddr_t table_item_addr = (dir_item.page_frame << 12) + (page << 2);
	PTE table_item = (PTE)hwaddr_read(table_item_addr, 4);

	/* get physical addr */
	hwaddr_t phy_addr = (table_item.page_frame << 12) + offset;

	return phy_addr;
}
extern void page_test(lnaddr_t addr)
{
	hwaddr_t hwaddr = page_translate(addr);
	printf("page addr-->physical addr: 0x%08x --> 0x%08x\n",addr, hwaddr);
}
