#ifndef __TLB_H__
#define __TLB_H__

/*tlb
	tlb 64 item
	fully associative
	valib bit
	random replace
*/

#define NR_ITEM 64

typedef struct{
	uint32_t tag;
	uint32_t phy_page;
	bool valid;
} TLB_line;

typedef struct TLB {
	TLB_line line[NR_ITEM];
	uint32_t nr_item;

	void (* init)(struct TLB *this);
	uint32_t (* check) (struct TLB *this,lnaddr_t addr, bool *state);
	void (* write) (struct TLB *this,lnaddr_t addr, hwaddr_t phy_page);
	void (* clean) (struct TLB *this);
} TLB;

extern TLB tlb;
#endif
