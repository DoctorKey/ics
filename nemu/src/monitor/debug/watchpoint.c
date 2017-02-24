#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

void display_wp()
{
	WP *wp;
	wp = head;
	if(wp == NULL){
		printf("no watchpoint!!\n");
	}else{
		while(wp != NULL){
			printf("watchpoint [%d]: %s value is 0x%x\t %d\n",wp->NO,wp->expression,wp->old_value,wp->old_value);
			wp = wp->next;
		}
	}
}
WP* new_wp()
{
	WP *wp,*target;
	if(free_ == NULL){
		printf("no more watchpoint!!\n");
		assert(0);
		return 0;
	}
	target = free_;
	free_ = free_->next;
	target->next = NULL;
	wp = head;
	if(wp == NULL){
		head = target;
	}else{
		while(wp->next != NULL)
			wp = wp->next;
		wp->next = target;
	}
	return target;	
}

bool check_watchpoint()
{
	bool change=false;
	bool state=false;
	WP *wp;
	wp = head;
	while(wp != NULL){
		wp->new_value = expr(wp->expression,&state);
		if(wp->new_value != wp->old_value){
			printf("watchpoint %d value change!!!\n",wp->NO);
			printf("%s : old_value=0x%x\t%d\n",wp->expression,wp->old_value,wp->old_value);
			printf("%s : new_value=0x%x\t%d\n",wp->expression,wp->new_value,wp->new_value);
			change = true;
			wp->old_value = wp->new_value;
		}
		wp = wp->next;
	}
	return change;
}

void free_wp(WP *wp)
{
	WP *piror;
	piror = head;
	if(piror == wp){
		head = wp->next;
	}else{
		while(piror->next != wp)
			piror = piror->next;
		piror->next = wp->next;
	}
	wp->next = free_;
	free_ = wp;
}

bool delete_wp(int n)
{
	WP *wp;
	wp = head;
	while(wp != NULL && wp->NO != n)
		wp = wp->next;
	if(wp == NULL)
		return false;
	else if(wp->NO == n){
		free_wp(wp);
		return true;
	}else
		return false;
}


