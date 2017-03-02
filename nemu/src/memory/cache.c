#include "common.h"
#include "burst.h"
#include "misc.h"
#include <stdlib.h>
#include <time.h>
#include "memory/cache.h"

extern uint32_t dram_read(hwaddr_t addr,size_t len);
extern void dram_write(hwaddr_t addr,size_t len,uint32_t data);

uint8_t read_cache_2_b(Cache_2 *this,hwaddr_t addr);
void write_cache_2_b(Cache_2 *this,hwaddr_t addr,uint8_t data);
/*cache_1
	cache block 64B
	cache 64KB
	8-way set associative
	valib bit
	random replace
	write through
	not write allocate
*/
uint8_t read_cache_b(Cache *this,hwaddr_t addr)
{
	int branch;
 	Cache_line temp;
	temp.addr = addr;
	int set = temp.set;
	int index = temp.index;
	int valid = 0;
	for(branch = 0;branch < this->nr_branch;branch++){
		if(this->line[set][branch].target == temp.target && this->line[set][branch].valid == true){
			//hit
			return unalign_rw(this->line[set][branch].buf + index,1);
		}
		if(this->line[set][branch].valid == false){
			valid = branch;
		}
	}
	//end loop , not hit
	//random find i branch
	if(valid == 0){
		srand((unsigned)time(NULL));
		branch = rand()%this->nr_branch;
		this->line[set][branch].valid = false;
	}else{
		branch = valid;
	}
	//copy block to  branch
	temp.index = 0;
	addr = temp.addr;
	int j;
	for(j = 0;j < this->nr_index;j++){
//		memset(this->line[set][branch].buf + j, dram_read(addr + j,1), 1);
		memset(this->line[set][branch].buf + j, read_cache_2_b(&cache_2, addr + j), 1);
	}
	this->line[set][branch].addr = addr;
	this->line[set][branch].valid = true;
	return unalign_rw(this->line[set][branch].buf + index,1);
}
uint32_t read_cache(Cache *this,hwaddr_t addr,size_t len)
{
	uint8_t temp[4] = {0};
	uint32_t result = 0;
	int i;
	for(i = 0;i < len;i++){
		temp[i] = read_cache_b(this,addr + i);
		result |= (temp[i]) << (8 * i);
	}
	return result;
}
extern void search_cache(Cache *this,uint32_t addr)
{
	int i;
 	Cache_line temp;
	temp.addr = addr;
	int set = temp.set;
	uint32_t result;
	for(i = 0;i < this->nr_branch;i++){
		if(this->line[set][i].target == temp.target && this->line[set][i].valid == true){
			//hit
			printf("addr(0x%08x) hit the cache!\n",addr);
			printf("target:0x%08x\tset:0x%08x\tindex:0x%08x\n",temp.target,temp.set,temp.index);
			result = unalign_rw(this->line[set][i].buf + temp.index, 4);
			printf("buf[0x%08x(%d)]:0x%08x\t%d\n",temp.index,temp.index,result,result);
			return;
		}
	}
	//end loop , not hit
	printf("not find addr in cache!\n");
}
void write_cache_b(Cache *this,hwaddr_t addr,uint8_t data)
{
	int i;
 	Cache_line temp;
	temp.addr = addr;
	int set = temp.set;
	for(i = 0;i < this->nr_branch;i++){
		if(this->line[set][i].target == temp.target && this->line[set][i].valid == true){
			//hit write through
			memset(this->line[set][i].buf + temp.index, data, 1);
			write_cache_2_b(&cache_2, addr, data);
			return;
		}
	}
	//end loop , not hit, not write allocate
	write_cache_2_b(&cache_2, addr, data);
	return;
}
void write_cache(Cache *this,hwaddr_t addr,size_t len,uint32_t data)
{
	uint8_t temp = 0;
	int i;
	for(i = 0;i < len;i++){
		temp = data & 0xff;
		write_cache_b(this,addr + i, temp);
		data = data >> 8;
	}
}
extern void init_cache(Cache *this)
{
	int i,j;
	this->nr_index = NR_INDEX_1;
	this->nr_set   = NR_SET_1;
	this->nr_branch= NR_BRANCH_1;
	this->write_through = true;
	this->write_allocate= true;

	this->read = read_cache;
	this->write = write_cache;
	for(i = 0;i < this->nr_set;i++){
		for(j = 0;j < this->nr_branch;j++){
			this->line[i][j].valid = false;
		}
	}
}

/*cache_2
	cache block 64B
	cache 4MB
	16-way set associative
	valib bit dirty bit
	random replace
	write back
	write allocate
*/
uint8_t read_cache_2_b(Cache_2 *this,hwaddr_t addr)
{
	int branch;
 	Cache_line_2 temp;
	temp.addr = addr;
	int set = temp.set;
	int index = temp.index;
	int valid = 0;
	for(branch = 0;branch < this->nr_branch;branch++){
		if(this->line[set][branch].target == temp.target && this->line[set][branch].valid == true){
			//hit
			return unalign_rw(this->line[set][branch].buf + index,1);
		}
		if(this->line[set][branch].valid == false){
			valid = branch;
		}
	}
	//end loop , not hit
	temp.index = 0;
	addr = temp.addr;
	int j;
	//random find i branch
	if(valid == 0){
		srand((unsigned)time(NULL));
		branch = rand()%this->nr_branch;
		/* write back */
		this->line[set][branch].valid = false;
		// write back
		if(this->line[set][branch].dirty == true){
			for(j = 0;j < this->nr_index;j++){
				dram_write(addr + j, 1, this->line[set][branch].buf[j]);
			}
			this->line[set][branch].dirty = false;
		}
	}else{
		branch = valid;
	}
	//copy block to  branch
	for(j = 0;j < this->nr_index;j++){
		memset(this->line[set][branch].buf + j, dram_read(addr + j,1), 1);
	}
	this->line[set][branch].addr = addr;
	this->line[set][branch].valid = true;
	return unalign_rw(this->line[set][branch].buf + index,1);
}
uint32_t read_cache_2(Cache_2 *this,hwaddr_t addr,size_t len)
{
	uint8_t temp[4] = {0};
	uint32_t result = 0;
	int i;
	for(i = 0;i < len;i++){
		temp[i] = read_cache_2_b(this,addr + i);
		result |= (temp[i]) << (8 * i);
	}
	return result;
}
extern void search_cache_2(Cache_2 *this,uint32_t addr)
{
	int i;
 	Cache_line_2 temp;
	temp.addr = addr;
	int set = temp.set;
	uint32_t result;
	for(i = 0;i < this->nr_branch;i++){
		if(this->line[set][i].target == temp.target && this->line[set][i].valid == true){
			//hit
			printf("addr(0x%08x) hit the cache_2!\n",addr);
			printf("target:0x%08x\tset:0x%08x\tindex:0x%08x\n",temp.target,temp.set,temp.index);
			result = unalign_rw(this->line[set][i].buf + temp.index, 4);
			printf("buf[0x%08x(%d)]:0x%08x\t%d\n",temp.index,temp.index,result,result);
			return;
		}
	}
	//end loop , not hit
	printf("not find addr in cache_2!\n");
}
void write_cache_2_b(Cache_2 *this,hwaddr_t addr,uint8_t data)
{
	int branch;
 	Cache_line_2 temp;
	temp.addr = addr;
	int index = temp.index;
	int set = temp.set;
	int valid = this->nr_branch;
	for(branch = 0;branch < this->nr_branch;branch++){
		if(this->line[set][branch].target == temp.target && this->line[set][branch].valid == true){
			//hit write cache
			memset(this->line[set][branch].buf + index, data, 1);
			this->line[set][branch].dirty = true;
			return;
		}
		if(this->line[set][branch].valid == false){
			valid = branch;
		}
	}
	//end loop , not hit
	/* update memory */
	dram_write(addr, 1, data);
	temp.index = 0;
	addr = temp.addr;
	int j;
	//random find branch
	if(valid == this->nr_branch){
		srand((unsigned)time(NULL));
		branch = rand()%this->nr_branch;
		/* write back */
		this->line[set][branch].valid = false;
		// write back
		if(this->line[set][branch].dirty == true){
			for(j = 0;j < this->nr_index;j++){
				dram_write(addr + j, 1, this->line[set][branch].buf[j]);
			}
			this->line[set][branch].dirty = false;
		}
	}else{
		branch = valid;
	}
	//copy block(have updated) to  branch
	for(j = 0;j < this->nr_index;j++){
		memset(this->line[set][branch].buf + j, dram_read(addr + j,1), 1);
	}
	this->line[set][branch].addr = addr;
	this->line[set][branch].valid = true;
	return;
}
void write_cache_2(Cache_2 *this,hwaddr_t addr,size_t len,uint32_t data)
{
	uint8_t temp = 0;
	int i;
	for(i = 0;i < len;i++){
		temp = data & 0xff;
		write_cache_2_b(this,addr + i, temp);
		data = data >> 8;
	}
}
extern void init_cache_2(Cache_2 *this)
{
	int i,j;
	this->nr_index = NR_INDEX_2;
	this->nr_set   = NR_SET_2;
	this->nr_branch= NR_BRANCH_2;
	this->write_through = false;
	this->write_allocate= false;

	this->read = read_cache_2;
	this->write = write_cache_2;
	for(i = 0;i < this->nr_set;i++){
		for(j = 0;j < this->nr_branch;j++){
			this->line[i][j].valid = false;
			this->line[i][j].dirty = false;
		}
	}
}
