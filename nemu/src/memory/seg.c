#include "common.h"
#include "burst.h"
#include "misc.h"
#include "cpu/reg.h"

lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg)
{
	/* run in real mode */
	if(cpu.cr0.protect_enable == 0){
		return addr;
	}

	/* run in protect mode */
	return addr;
}
