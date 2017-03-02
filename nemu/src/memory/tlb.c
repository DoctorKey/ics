#include "common.h"
#include "burst.h"
#include "misc.h"
#include <stdlib.h>
#include <time.h>
#include "memory/tlb.h"

/*tlb
	tlb 64 item
	fully associative
	valib bit
	random replace
*/

uint32_t check_tlb(TLB *this,lnaddr_t addr, bool *state)
{
	uint32_t lnaddr_tag = addr & 0xfffff000;
	int i;
	for(i = 0; i < this->nr_item; i++){
		if(this->line[i].valid == true && this->line[i].tag == lnaddr_tag){
			*state = true;
			return this->line[i].phy_page;
		}
	}
	*state = false;
	return addr;
}
void write_tlb(TLB *this,hwaddr_t addr,hwaddr_t phy_page)
{
	int i;
	for(i = 0;i < this->nr_item;i++){
		/* find a valid item */
		if(this->line[i].valid == false){
			//just save high 20 bit
			this->line[i].tag = addr & 0xfffff000;
			this->line[i].phy_page = phy_page & 0xfffff000;
			this->line[i].valid = true;
			return;
		}
	}
	//end loop , not hit, not write allocate
	srand((unsigned)time(NULL));
	i = rand()%this->nr_item;
	this->line[i].valid = false;
	//replace
	this->line[i].tag = addr & 0xfffff000;
	this->line[i].phy_page = phy_page & 0xfffff000;
	this->line[i].valid = true;
	return;
}
void clean_tlb(TLB *this)
{
	int i;
	for(i = 0; i < this->nr_item; i++){
		this->line[i].valid = false;
	}
}
extern void init_tlb(TLB *this)
{
	int i;
	this->nr_item = NR_ITEM;

	this->check = check_tlb;
	this->write = write_tlb;
	this->clean = clean_tlb;
	for(i = 0;i < this->nr_item;i++){
		this->line[i].valid = false;
	}
}


