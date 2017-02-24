#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */
	char expression[64];//64 chars may be not enough
	uint32_t old_value;//need store to check valuse change
	uint32_t new_value;//need store to check valuse change

} WP;

//WP* new_wp();
//void free_wp(WP *wp)
//bool check_watchpoint();
#endif
