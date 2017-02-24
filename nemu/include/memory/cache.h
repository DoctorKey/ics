#ifndef __CACHE_H__
#define __CACHE_H__

/*cache_1
	cache block 64B
	cache 64KB
	8-way set associative
	valib bit
	random replace
	write through
	not write allocate
*/
#define INDEX_WIDTH_1 6	//2^6=64
#define SET_WIDTH_1 7	//2^7=125 sets,every set has 8 branch
#define TARGET_WIDTH_1 (32 - SET_WIDTH_1 - INDEX_WIDTH_1)	//19
#define CACHE_WIDTH_1 16	//2^16=64KB

#define NR_INDEX_1 (1 << INDEX_WIDTH_1)
#define NR_SET_1 (1 << SET_WIDTH_1)
#define NR_TARGET_1 (1 << TARGET_WIDTH_1)
#define NR_BRANCH_1 (1 << (CACHE_WIDTH_1 - INDEX_WIDTH_1 - SET_WIDTH_1))	//2^3=8


typedef struct{
	union {
		struct {
			uint32_t index	: INDEX_WIDTH_1;
			uint32_t set	: SET_WIDTH_1;
			uint32_t target	: TARGET_WIDTH_1;
		};
		uint32_t addr;
	};
	uint8_t buf[NR_INDEX_1];
	bool valid;
	bool dirty;
} Cache_line;

typedef struct Cache {
	Cache_line line[NR_SET_1][NR_BRANCH_1];
	uint32_t nr_index;
	uint32_t nr_set;
	uint32_t nr_branch;
	bool write_through;	//true:write_through	false:write_back
	bool write_allocate;	//true:write_allocate	false:not write allocate

	void (* init)(struct Cache *this);
	uint32_t (* read) (struct Cache *this,hwaddr_t addr,size_t len);
	void (* write) (struct Cache *this,hwaddr_t addr,size_t len,uint32_t data);
} Cache;

extern Cache cache_1;
/*cache_2
	cache block 64B
	cache 4MB 
	16-way set associative
	valib bit dirty bit
	random replace
	write back
	write allocate
*/
#define INDEX_WIDTH_2 6	//2^6=64
#define SET_WIDTH_2 12	//2^12=4096 sets,every set has 8 branch
#define TARGET_WIDTH_2 (32 - SET_WIDTH_2 - INDEX_WIDTH_2)	//14
#define CACHE_WIDTH_2 22	//2^22=4MB

#define NR_INDEX_2 (1 << INDEX_WIDTH_2)
#define NR_SET_2 (1 << SET_WIDTH_2)
#define NR_TARGET_2 (1 << TARGET_WIDTH_2)
#define NR_BRANCH_2 (1 << (CACHE_WIDTH_2 - INDEX_WIDTH_2 - SET_WIDTH_2))	//2^4=16


typedef struct{
	union {
		struct {
			uint32_t index	: INDEX_WIDTH_2;
			uint32_t set	: SET_WIDTH_2;
			uint32_t target	: TARGET_WIDTH_2;
		};
		uint32_t addr;
	};
	uint8_t buf[NR_INDEX_2];
	bool valid;
	bool dirty;
} Cache_line_2;

typedef struct Cache_2 {
	Cache_line_2 line[NR_SET_2][NR_BRANCH_2];
	uint32_t nr_index;
	uint32_t nr_set;
	uint32_t nr_branch;
	bool write_through;	//true:write_through	false:write_back
	bool write_allocate;	//true:write_allocate	false:not write allocate

	void (* init)(struct Cache_2 *this);
	uint32_t (* read) (struct Cache_2 *this,hwaddr_t addr,size_t len);
	void (* write) (struct Cache_2 *this,hwaddr_t addr,size_t len,uint32_t data);
} Cache_2;

extern Cache_2 cache_2;

#endif
