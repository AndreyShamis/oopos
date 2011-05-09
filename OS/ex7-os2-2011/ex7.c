//=============================================================================
//	Students 
//				Andrey Shamis		321470882
//				Ilia Gaysinsky		30
//
//=============================================================================

#include <stdio.h>		//	standrard I/O
#include <stdlib.h>		//	used for EXIT_SUCCESS
#include <math.h>		//	used for rand
#include <time.h>		//	used for srand
//=============================================================================

#define TEXT_SIZE 256	//	size of text segment of executable
#define DATA_SIZE 256 	//	size of data segment of executable	
#define BSS_SIZE 256	//	size of bss segment of executable	
#define LETTER_START 65 // 	first capital letter in ascii table
#define DIFF 25			//	range of capital letters in ascii table
#define EXEC_FILE "exec"

#define LOOPS 200
#define PHISYCAL_MEM_SIZE 64

#define EXEC_SIZE 1024

//=============================================================================



char MEM[PHISYCAL_MEM_SIZE];
//=============================================================================



typedef struct page_descriptor
{
	short int Valid;
	short int Permission;
	short int Touched;
	int Frame;
}page_descriptor;

typedef struct sim_database
{
	page_descriptor ptable[PHISYCAL_MEM_SIZE];

	

	char *swap_file;
	char *swap_fd;

	char *program_file;
	char *program_fd;	

}sim_database; 



//=============================================================================

//=============================================================================
void CreateMEM()
{
	;

}

//=============================================================================

void CreateSwap()
{
	;
}
//=============================================================================
void CreateVM()
{
	;

}



sim_database *vm_constructor(char *executable,unsigned short text,
unsigned short data,unsigned short bss)
{

	
	sim_database *ret=NULL;
	
	
	return(ret);
}
//=============================================================================
char vm_load(sim_database *sim_db,unsigned short virtual_addr)
{

	return('a');
}
//=============================================================================
int vm_store(sim_database *sim_db,unsigned short virtual_addr,
						unsigned char value)
{

	return(0);
}
//=============================================================================
void vm_destructor(sim_database *sim_db)
{

	;
}

int vm_print(sim_database *sim_db)
{

	return(0);
}

//=============================================================================

int main()
{

	srand(time(NULL));
	
	sim_database *sim_db = vm_constructor(EXEC_FILE,TEXT_SIZE,DATA_SIZE, BSS_SIZE);
	
	int i;
	unsigned short addr;
	unsigned char *val = NULL;
	for(i=0;i<LOOPS;i++)
	{
		addr = rand()%EXEC_SIZE;
		*val = vm_load(sim_db,addr);
		*val = rand() %DIFF +LETTER_START;
		vm_store(sim_db,addr+1,*val);
	
	}
	
	vm_print(sim_db);
	vm_destructor(sim_db);
	
//	CreateMEM();
//	CreateSwap();
//	CreateVM();
	
	return(EXIT_SUCCESS);
	
}



//=============================================================================
//=============================================================================
//=============================================================================









