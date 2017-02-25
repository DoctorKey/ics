#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"
#include "memory/cache.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);
WP* new_wp();
bool delete_wp(int);
void display_wp();

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_si(char *args){
	char *arg = strtok(NULL," ");
	int num;
	
	if (arg == NULL){
		/*default is 1 */
		num = 1;
		cpu_exec(num);
		return 0;
	}else{
		num = atoi(arg);
//		if(num >= MAX_INSTR_TO_PRINT)
//			num = MAX_INSTR_TO_PRINT;
		cpu_exec(num);
		return 0; 
	}	
}

static int cmd_info(char *args){
	char *arg = strtok(NULL," ");
	
	if(arg != NULL && strcmp(arg,"r")==0){
		/*print the reg */
		printf("---------------------------------------------------------------------\n");
		printf("name\tvalue(16)\tvalue(10)\t|seg\tvalue(16)\tindex(16)\n");
		printf("eax\t0x%08x\t%010d\t|es\t0x%08x\t0x%08x\n",cpu.eax,cpu.eax,cpu.es.val,cpu.es.INDEX);
		printf("ecx\t0x%08x\t%010d\t|cs\t0x%08x\t0x%08x\n",cpu.ecx,cpu.ecx,cpu.cs.val,cpu.cs.INDEX);
		printf("edx\t0x%08x\t%010d\t|ss\t0x%08x\t0x%08x\n",cpu.edx,cpu.edx,cpu.ss.val,cpu.ss.INDEX);
		printf("ebx\t0x%08x\t%010d\t|ds\t0x%08x\t0x%08x\n",cpu.ebx,cpu.ebx,cpu.ds.val,cpu.ds.INDEX);
		printf("esp\t0x%08x\t%010d\t|GDTR\tGDTR_LIM\n",cpu.esp,cpu.esp);
		printf("ebp\t0x%08x\t%010d\t|0x%08x\t0x%04x\n",cpu.ebp,cpu.ebp,cpu.GDTR,cpu.GDTR_LIM);
		printf("esi\t0x%08x\t%010d\n",cpu.esi,cpu.esi);
		printf("edi\t0x%08x\t%010d\n",cpu.edi,cpu.edi);
		printf("CF=%d\tPF=%d\tZF=%d\tSF=%d\tIF=%d\tDF=%d\tOF=%d\t\n",
			cpu.EFLAGS.CF,cpu.EFLAGS.PF,cpu.EFLAGS.ZF,cpu.EFLAGS.SF,cpu.EFLAGS.IF,cpu.EFLAGS.DF,cpu.EFLAGS.OF);
		printf("eip\t0x%08x\t%d\n",cpu.eip,cpu.eip);
		printf("-----------------------------------\n");
		return 0;
	}
	if(arg != NULL && strcmp(arg,"w")==0){
		/*print the watchpoint*/
		display_wp();
		return 0;
	}
	/*command error*/
	printf("command error!\n");
	return 0;
}
static int cmd_x(char *args){
	char *arg = strtok(NULL," ");
	bool state;
	int num,i;
	uint32_t result;
	
	num = strtol(arg,NULL,10);
	arg = strtok(NULL," ");
	result = expr(arg,&state);
	for(i = 1;i <= num;i++){
		printf("0x%08x:\t0x%08x\t%d\n",result,swaddr_read(result,4,R_DS),swaddr_read(result,4,R_DS));
		result += 4;
	}
	return 0;
}
static int cmd_p(char *args){
	char *arg = strtok(NULL," ");
	bool state;
	uint32_t result;
	
	result = expr(arg,&state);
	if(state == false){
		printf("expression compute false!!!\n");
		return 0;
	}else{
		printf("the result is : 0x%0x\t%d\n",result,result);
		return 0;
	}
}	
static int cmd_w(char *args){
	char *arg = strtok(NULL," ");
	bool state;
	WP *wp;
	
	wp = new_wp();
	strcpy(wp->expression,arg);
	wp->old_value = expr(wp->expression,&state);
	wp->new_value = wp->old_value;
	if(state == false){
		printf("expression compute false!!!\n");
		return 0;
	}else{
		printf("watchpoint %d: %s is 0x%0x\t%d\n",wp->NO,wp->expression,wp->old_value,wp->old_value);
		return 0;
	}
}
static int cmd_d(char *args){
	char *arg = strtok(NULL," ");
	int num;
	bool state;
	
	num = strtol(arg,NULL,10);
	state = delete_wp(num);
	if(state == false){
		printf("not delete!!!\n");
		return 0;
	}else{
		printf("watchpoint %d have deleted\n",num);
		return 0;
	}
}	
int cmd_bt_elf();
static int cmd_bt()
{
	return cmd_bt_elf();
}
Cache cache_1;
void search_cache(Cache *this,uint32_t addr);
Cache_2 cache_2;
void search_cache_2(Cache_2 *this,uint32_t addr);
static int cmd_cache(char *args){
	char *arg = strtok(NULL," ");
	bool state;
	uint32_t result;
	
	result = expr(arg,&state);
	if(state == false){
		printf("expression compute false!!!\n");
		return 0;
	}else{
		printf("the address is : 0x%0x\n",result);
		search_cache(&cache_1,result);
		search_cache_2(&cache_2,result);
		return 0;
	}
}
static int cmd_help(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "execution by step",cmd_si },
	{ "info", "info r: print reg  info w: prinf watchpoint",cmd_info},
	{ "p", "p EXPR: compute the code ",cmd_p},
	{ "x", "x N EXPR: scan the ram" ,cmd_x},
	{ "w", "w EXPR: set the watchpoint",cmd_w},
	{ "d", "d N: delet N watchpoint",cmd_d},
	{ "bt", "print the scan chain" ,cmd_bt},
	{ "cache", "cache ADDR: detect cache" ,cmd_cache},
};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
