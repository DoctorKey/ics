#include "nemu.h"
#include <stdlib.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ

	/* TODO: Add more token types */
	,NUM_10,NUM_16,REG,NEQ,AND,OR,NOR,DEREF,VAR
};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"0x[[:xdigit:]][[:xdigit:]]*", NUM_16},
	{"[0-9][0-9]*", NUM_10},
	{"\\$[[:alpha:]][[:alpha:]]*", REG},
	{"[[:alpha:]_][[:alpha:]_]*", VAR},
	{"\\(",'('},
	{"\\)",')'},
	{"\\*",'*'},
	{"\\/",'/'},
	{"\\+", '+'},
	{"\\-",'-'},	
	{"==", EQ},		
	{"\\!=", NEQ},			
	{"&&", AND},				
	{"\\|\\|", OR},						
	{"\\!", NOR}					
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

//				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

/*
				switch(rules[i].token_type) {
				case NUM_10:
					tokens[nr_token].type = NUM_10;
					break;
				case NUM_16:
					tokens[nr_token].type = NUM_16;
					break;
				case REG:tokens[nr_token].type = REG;break;
				case NOTYPE:
					tokens[nr_token].type = NOTYPE;
					break;
				case EQ:
					tokens[nr_token].type = EQ;
					break;
				case '(':
					tokens[nr_token].type = '(';
					break;
				case ')':
					tokens[nr_token].type = ')';
					break;
				case '+':
					tokens[nr_token].type = '+';
					break;
				case '-':
					tokens[nr_token].type = '-';
					break;
				case '*':
					tokens[nr_token].type = '*';
					break;
				case '/':
					tokens[nr_token].type = '/';
					break;
					default: panic("please implement me");
				}
*/
				tokens[nr_token].type=rules[i].token_type;
				strncpy(tokens[nr_token].str,substr_start,substr_len);
				nr_token++;
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}
/* a match pair of parentheses return true
* otherwise return false
*/
static bool check_parentheses(int p,int q)
{
	int point,num=0;
	if(tokens[p].type == '(' && tokens[q].type == ')'){
	}else{
		return false;
	}
	for(point = p + 1;point < q;point++){
		if(tokens[point].type == '('){
			num++;
		}else if(tokens[point].type == ')'){
			if(num == 0)
				return false;
			num--;
		}
	}	
	if(num == 0)
		return true;
	else
		return false;
}
static int find_dominant_operator(int p,int q)
{
	int point;
	int level=6;	
/*	low:	1: == !=
		2: && ||
		3: + -
		4: * /
		5: ! *
*/
	int op=p;
	for(point = p;point <= q;point++){
		if(tokens[point].type == NUM_10 || tokens[point].type == NUM_16 || tokens[point].type == REG || tokens[point].type == VAR)
			continue;
		if(tokens[point].type == '('){
			while(point <= q && tokens[point].type != ')')
				point++;
			if(point == q)
				return op;
		}
		if(tokens[point].type == EQ || tokens[point].type == NEQ){
			level = 1;
			op = point;	
			continue;	
		}
		if(tokens[point].type == AND || tokens[point].type == OR){
			if(level >= 2){
				level = 2;
				op = point;	
			}
			continue;	
		}
		if(tokens[point].type == '+' || tokens[point].type == '-'){
			if(level >= 3){
				level = 3;
				op = point;	
			}
			continue;	
		}
		if(tokens[point].type == '*' || tokens[point].type == '/'){
			if(level >= 4){
				level = 4;
				op = point;	
			}
			continue;	
		}
		if(tokens[point].type == NOR || tokens[point].type == DEREF){
			if(level >= 5){
				level = 5;
				op = point;	
			}
			continue;	
		}
	}
	return op;
}
static uint32_t eval_reg(int p)
{
	if(strcmp(tokens[p].str + 1,"eax")==0)
		return cpu.eax;
	if(strcmp(tokens[p].str + 1,"ecx")==0)
		return cpu.ecx;
	if(strcmp(tokens[p].str + 1,"edx")==0)
		return cpu.edx;
	if(strcmp(tokens[p].str + 1,"ebx")==0)
		return cpu.ebx;
	if(strcmp(tokens[p].str + 1,"esp")==0)
		return cpu.esp;
	if(strcmp(tokens[p].str + 1,"ebp")==0)
		return cpu.ebp;
	if(strcmp(tokens[p].str + 1,"esi")==0)
		return cpu.esi;
	if(strcmp(tokens[p].str + 1,"edi")==0)
		return cpu.edi;
	if(strcmp(tokens[p].str + 1,"eip")==0)
		return cpu.eip;
	printf("false name of reg!!--%s\n",tokens[p].str);
	return 0;
} 
uint32_t eval_sym(char *str);
static uint32_t eval_var(int p)
{
	return eval_sym(tokens[p].str);	
}
uint32_t eval(int p,int q)
{
	int op;
	uint32_t val1=0,val2;
	if(p>q){
		/*bad expression*/
		printf("bad expression p > q\n");
		assert(0);
		return 0;
	}else if(p==q){
		/*single token
		 * for now this token should be a number.
		 * return the value of the number
		 */
		switch(tokens[p].type){
		case NUM_10:return strtol(tokens[p].str,NULL,10);break;
		//case NUM_16:return strtol(tokens[p].str,NULL,16);break;
		case NUM_16:return strtoul(tokens[p].str,NULL,16);break;
		case REG:return eval_reg(p);break;
		case VAR:return eval_var(p);break;
		default:printf("no number type!! return 0!!\n");
			return 0;
		}
	}else if( check_parentheses(p,q) == true){
		/* the expression is surrounded by a matched pair of parentheses.
		 * if that is the case,just throw away the parentheses
		 */
		return eval(p+1,q-1);
	}else{
		op = find_dominant_operator(p,q);
		if(tokens[op].type != NOR && tokens[op].type!= DEREF)
			val1 = eval( p , op-1 );
		val2 = eval( op+1 , q );

		switch(tokens[op].type){
		case '+':return val1 + val2;
		case '-':return val1 - val2;
		case '*':return val1 * val2;
		case '/':return val1 / val2;
		case EQ :return val1==val2;
		case NEQ:return val1!=val2;
		case AND:return val1&&val2;
		case OR :return val1||val2;
		case NOR:return !val2;
		case DEREF :return swaddr_read(val2,4,R_DS);//the second input may no use
		default:
			printf("the op_type is %c\n",tokens[op].type);
			assert(0);
		}
	}
}

uint32_t expr(char *e, bool *success) {
	int i,j;
	/*init tokens */
	for(i = 0;i < 32;i++){
		for(j = 0;j < 32;j++){
			tokens[i].str[j] = 0;	
		}
		tokens[i].type = 0;
	}

	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	*success = true;

	for(i = 0;i < nr_token;i++){
		if(tokens[i].type == '*' && (i == 0 ||
			 (tokens[i - 1].type != NUM_10 && tokens[i - 1].type != NUM_16 && tokens[i - 1].type != REG) ))
		{
			tokens[i].type = DEREF;
			Log("change tokens[%d].type = DEREF",i);
		}
	}
	return eval(0,nr_token-1);
}

