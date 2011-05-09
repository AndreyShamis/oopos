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
#include <unistd.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

	

	char 	*swap_file;
	int 	swap_fd;

	char 	*program_file;
	int 	program_fd;	

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
	
	//	Craete and set ptable
	sim_database *ret=NULL;	
	
	//int pageTableSize = 1024;
	ret = (sim_database *) malloc(1); 	
	if(ret == NULL)
	{
		perror("Cannot allocate memory\n");
		exit(EXIT_FAILURE);
	}
	//	Open SWAP file in correct size
	ret->swap_fd 	= open("swap_file",O_CREAT | O_RDWR | O_TRUNC);
	
	//	Open program file
	ret->program_fd 	= open(executable,O_RDWR | O_CREAT);
	//ret->swap_file = "swap_file";
	ret->program_file = executable;
	return(ret);
}
//=============================================================================
char vm_load(sim_database *sim_db,unsigned short virtual_addr)
{
/*
	if(virtual_addr <= DATA_SIZE+TEXT_SIZE)
	{
	
	}
	else if(virtual_addr >DATA_SIZE+TEXT_SIZE+BSS)
	{
	
	}
	else
	{
		
	}
*/
	
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
	close(sim_db->swap_fd);
	close(sim_db->program_fd);
	
	free(sim_db);
}

int vm_print(sim_database *sim_db)
{
	
	printf("Swap descriptor %d\n",sim_db->swap_fd);
	printf("File descriptor %d\n",sim_db->program_fd);
	return(0);
}

//=============================================================================

int main()
{

	srand(time(NULL));
	
	sim_database *sim_db = vm_constructor(EXEC_FILE,TEXT_SIZE,DATA_SIZE, BSS_SIZE);
	
	
	int i;
	unsigned short addr;
	unsigned char val ;
	for(i=0;i<LOOPS;i++)
	{
		addr = rand()%EXEC_SIZE;
		val = vm_load(sim_db,addr);
	//	val = rand() %DIFF +LETTER_START;
	//	vm_store(sim_db,addr+1,val);
	
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









