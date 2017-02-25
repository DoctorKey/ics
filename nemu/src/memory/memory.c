#include "common.h"
#include "memory/cache.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
lnaddr_t seg_translate(swaddr_t, size_t, uint8_t);
Cache cache_1;
Cache_2 cache_2;

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	/* disk */
//	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));

	/* cache_1 --> cache_2 --> disk */
	return cache_1.read(&cache_1,addr, len) & (~0u >> ((4 - len) << 3));

	/* cache_2 --> disk */
//	return cache_2.read(&cache_2,addr, len) & (~0u >> ((4 - len) << 3));
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	/* disk */
//	dram_write(addr, len, data);

	/* cache_1 --> cache_2 --> disk */
	cache_1.write(&cache_1, addr, len, data);

	/* cache_2 --> disk */
//	cache_2.write(&cache_2, addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr = seg_translate(addr, len, sreg);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint8_t sreg, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr = seg_translate(addr, len, sreg);
	lnaddr_write(lnaddr, len, data);
}

