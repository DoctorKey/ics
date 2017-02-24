#include "common.h"
#include "nemu.h"
#include <stdlib.h>
#include <elf.h>

#define STACK_NUM 10

char *exec_file = NULL;

static char *strtab = NULL;
static Elf32_Sym *symtab = NULL;
static int nr_symtab_entry;

extern uint32_t eval_sym(char *str)
{
	int i=1;
	for(i = 1;i <= nr_symtab_entry;i++){
		if(symtab[i].st_info == 17){
			if(strcmp(str,strtab+symtab[i].st_name) == 0){
				printf("var %s : 0x%08x\t%d\n",strtab+symtab[i].st_name,symtab[i].st_value,symtab[i].st_value);
				return symtab[i].st_value;
			}
		}
	}
	printf("don't find var!!\n");
	for(i = 1;i <= nr_symtab_entry;i++){
		if(symtab[i].st_info == 17){
			printf("var %s : 0x%08x\t%d\n",strtab+symtab[i].st_name,symtab[i].st_value,symtab[i].st_value);
		}
	}
	return 0;
}
typedef struct{
	swaddr_t prev_ebp;
	swaddr_t ret_addr;
	uint32_t args[4];
}PartOfStackFrame;
extern int cmd_bt_elf()
{
	PartOfStackFrame stack[STACK_NUM];
	uint32_t ebp = cpu.ebp;
	int i = 0,num;
	while(ebp != 0){
		printf("ebp = 0x%08x\tret_addr = 0x%08x\n",ebp,swaddr_read(ebp + 4,4));
		stack[i].ret_addr = swaddr_read(ebp + 4,4);
		stack[i].args[0] = swaddr_read(ebp + 8,4);
		stack[i].args[1] = swaddr_read(ebp + 12,4);
		stack[i].args[2] = swaddr_read(ebp + 16,4);
		stack[i].args[3] = swaddr_read(ebp + 20,4);
		stack[i].prev_ebp = swaddr_read(ebp,4);
		ebp = swaddr_read(ebp,4);
		i++;
	}
	num = i;
	int j;
	for(i = 1;i <= nr_symtab_entry;i++){
		if(symtab[i].st_info == 18){
			if(symtab[i].st_value < cpu.eip && cpu.eip < symtab[i].st_value + symtab[i].st_size){
				printf("function %s ( %d , %d , %d , %d )\n",
					strtab+symtab[i].st_name,stack[0].args[0],stack[0].args[1],stack[0].args[2],stack[0].args[3]);
			}
		}
	}	
	for(j = 0;j < num;j++){
		for(i = 1;i <= nr_symtab_entry;i++){
			if(symtab[i].st_info == 18){
				if(symtab[i].st_value < stack[j].ret_addr && stack[j].ret_addr < symtab[i].st_value + symtab[i].st_size){
					printf("function %s ( %d , %d , %d , %d )\n",
						strtab+symtab[i].st_name,
						stack[j+1].args[0],stack[j+1].args[1],stack[j+1].args[2],stack[j+1].args[3]);
				}
			}
		}	
	}
	return 0;
}
void load_elf_tables(int argc, char *argv[]) {
	int ret;
	Assert(argc == 2, "run NEMU with format 'nemu [program]'");
	exec_file = argv[1];

	FILE *fp = fopen(exec_file, "rb");
	Assert(fp, "Can not open '%s'", exec_file);

	uint8_t buf[sizeof(Elf32_Ehdr)];
	ret = fread(buf, sizeof(Elf32_Ehdr), 1, fp);
	assert(ret == 1);

	/* The first several bytes contain the ELF header. */
	Elf32_Ehdr *elf = (void *)buf;
	char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

	/* Check ELF header */
	assert(memcmp(elf->e_ident, magic, 4) == 0);		// magic number
	assert(elf->e_ident[EI_CLASS] == ELFCLASS32);		// 32-bit architecture
	assert(elf->e_ident[EI_DATA] == ELFDATA2LSB);		// littel-endian
	assert(elf->e_ident[EI_VERSION] == EV_CURRENT);		// current version
	assert(elf->e_ident[EI_OSABI] == ELFOSABI_SYSV || 	// UNIX System V ABI
			elf->e_ident[EI_OSABI] == ELFOSABI_LINUX); 	// UNIX - GNU
	assert(elf->e_ident[EI_ABIVERSION] == 0);			// should be 0
	assert(elf->e_type == ET_EXEC);						// executable file
	assert(elf->e_machine == EM_386);					// Intel 80386 architecture
	assert(elf->e_version == EV_CURRENT);				// current version


	/* Load symbol table and string table for future use */

	/* Load section header table */
	uint32_t sh_size = elf->e_shentsize * elf->e_shnum;
	Elf32_Shdr *sh = malloc(sh_size);
	fseek(fp, elf->e_shoff, SEEK_SET);
	ret = fread(sh, sh_size, 1, fp);
	assert(ret == 1);

	/* Load section header string table */
	char *shstrtab = malloc(sh[elf->e_shstrndx].sh_size);
	fseek(fp, sh[elf->e_shstrndx].sh_offset, SEEK_SET);
	ret = fread(shstrtab, sh[elf->e_shstrndx].sh_size, 1, fp);
	assert(ret == 1);

	int i;
	for(i = 0; i < elf->e_shnum; i ++) {
		if(sh[i].sh_type == SHT_SYMTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".symtab") == 0) {
			/* Load symbol table from exec_file */
			symtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			ret = fread(symtab, sh[i].sh_size, 1, fp);
			assert(ret == 1);
			nr_symtab_entry = sh[i].sh_size / sizeof(symtab[0]);
		}
		else if(sh[i].sh_type == SHT_STRTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".strtab") == 0) {
			/* Load string table from exec_file */
			strtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			ret = fread(strtab, sh[i].sh_size, 1, fp);
			assert(ret == 1);
		}
	}

	free(sh);
	free(shstrtab);

	assert(strtab != NULL && symtab != NULL);

	fclose(fp);
}

