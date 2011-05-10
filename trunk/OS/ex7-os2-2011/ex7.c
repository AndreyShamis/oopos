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
#include <string.h>

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
#define SWAP_FILE "swap_file"

#define P_SIZE 16
#define LOOPS 200
#define PHISYCAL_MEM_SIZE 64

#define EXEC_SIZE 1024
#define PAGE_NUM 64

#define SWAP 	11
#define HARD 	12
#define MMEM	13

#define TEXT_R 	0
#define DATA_R 	1
#define BSS_R	2
#define HEAP_R  3
//=============================================================================



char MEM[PHISYCAL_MEM_SIZE];
int BLOCKS[4];
unsigned int BLOCKS_T[4];
int block_used;
unsigned int FCFS = 0;
//=============================================================================



typedef struct page_descriptor
{
	unsigned int valid;
	unsigned int permission;
	unsigned int touched;
	unsigned int frame;
}page_descriptor;

typedef struct sim_database
{
	page_descriptor *ptable;	

	char 	*swap_file;
	int 	swap_fd;

	char 	*program_file;
	int 	program_fd;	

}sim_database; 

//=============================================================================
void vm_destructor(sim_database *sim_db)
{
	printf("Close files...\n");
	close(sim_db->swap_fd);
	close(sim_db->program_fd);
	
	printf("Clear memory\n");
	free(sim_db->ptable);
	free(sim_db);
}

//=============================================================================

sim_database *vm_constructor(char *executable,unsigned short text,
unsigned short data,unsigned short bss)
{
	
	BLOCKS[0] = 0;
	BLOCKS[1] = 0;
	BLOCKS[2] = 0;
	BLOCKS[3] = 0;
	block_used = 0;
	//	Craete and set ptable
	sim_database *ret=NULL;		
	//	Allcocate memory for main data base
	ret = (sim_database *) malloc(sizeof(sim_database));
	
	//	Allocate memory for page table
	ret->ptable = (page_descriptor *) malloc(PAGE_NUM*sizeof(page_descriptor)); 
		
	//-------------------------------------------------------------------------
	//	Check if allocated
	if(ret == NULL || ret->ptable == NULL)
	{
		perror("Cannot allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	//-------------------------------------------------------------------------
	//	Open SWAP file in correct size
	ret->swap_file = (char *)malloc(strlen(SWAP_FILE)*sizeof(char));
	//	EXPECTED CHECK ALLOCATING
	strcpy(ret->swap_file,SWAP_FILE);
	ret->swap_fd 	= open(ret->swap_file,O_CREAT | O_RDWR | O_TRUNC);
	
	//	Open program file
	ret->program_fd 	= open(executable,O_RDWR | O_CREAT);
	//ret->swap_file = "swap_file";
	ret->program_file = executable;
	//char text[TEXT_SIZE];
	//char data[DATA_SIZE];
	//char bss[BSS_SIZE];
	//read(program_fd,text,TEXT_SIZE);
	//read(program_fd,data,DATA_SIZE);
	//read(program_fd,bss,BSS_SIZE);
	
		
	//-------------------------------------------------------------------------
	int i=0;
	short int section = TEXT_R;
	printf("Start fill table\n");
	for(i=0;i<PAGE_NUM;i++)
	{
		if(i*P_SIZE > TEXT_SIZE && section == 0)
		{
			section=DATA_R;
		}
		if(i*P_SIZE > TEXT_SIZE +DATA_SIZE && section == 1)
		{
			section = BSS_R;
		}
		if(i*P_SIZE > TEXT_SIZE+DATA_SIZE+BSS_SIZE && section == 2)
		{
			section=HEAP_R;
		}
		
		ret->ptable[i].valid 		= 0;
		if(section == HEAP_R || section == BSS_R || section == DATA_R)
			ret->ptable[i].permission 	= 1;
		else
			ret->ptable[i].permission 	= 0;
			
		ret->ptable[i].touched 		= 0;
		ret->ptable[i].frame 		= HARD;
	}
	
	return(ret);
}


void swap_out(sim_database *sim_db,const short int table,const short int block)
{
	char buff[P_SIZE];
	int i = 0;
	if(sim_db->ptable[table].touched)
	{
	
		for(i=0;i<P_SIZE;i++)
		{
			buff[i] = MEM[block+i];  
		}
		printf("2 - Table %d . Block: %d\n", table,block);
		lseek(sim_db->swap_fd,table*P_SIZE,SEEK_SET);
		write(sim_db->swap_fd,buff,P_SIZE);	
		sim_db->ptable[table].frame = SWAP;
		sim_db->ptable[table].valid = 0;
	}
	block_used--;
}
//=============================================================================
short int getFreeBlock(sim_database *sim_db)
{
	if(block_used < 4)
	{
		int i = 0;
		for(i=0;i<4;i++)
		{
			if(BLOCKS[i] == 0)
			{
				return(i);
			}
		}
	}
	else
	{
		int i=0;
		short int block_f=BLOCKS_T[0];
		unsigned int tm=-1;
		//printf("Trying to clear mem block\n");
		for(i=0;i<4;i++)
		{
			if(BLOCKS_T[i] < tm)
			{

				tm = BLOCKS_T[i];
				block_f = i;
			}
		}
		swap_out(sim_db,BLOCKS[block_f],block_f);
		return(block_f);
	}
	
	return(0);
}

//=============================================================================
char vm_load(sim_database *sim_db,unsigned short virtual_addr)
{
	if(virtual_addr >=1024)
	{
		printf("Big memory adress request\n");
	
	}
	
	//	HUY ZNAET CHTO
	unsigned short offset =	virtual_addr & 15;
	unsigned short page_table = virtual_addr>>4 ;

	char buff[P_SIZE];			//		Buffer for reading
	if(sim_db->ptable[page_table].valid == 1)
	{
		//	In main memory
		return(MEM[offset]);
	}
	else if(sim_db->ptable[page_table].valid == 0)
	{

		if(sim_db->ptable[page_table].frame == SWAP)
		{
			//	Go to SWAP
			printf("Read from swap\n");
			lseek(sim_db->swap_fd,page_table*P_SIZE,SEEK_SET);
			read(sim_db->swap_fd, buff,P_SIZE);	
		}
		else if(sim_db->ptable[page_table].frame == HARD)
		{
			//	Go to HARD			
			lseek(sim_db->program_fd,page_table*P_SIZE,SEEK_SET);
			read(sim_db->program_fd, buff,P_SIZE);		
		}
		else
		{
			printf("\t-\t-\t-\tError\n");
		}
		int i=0;
		short int block_us = getFreeBlock(sim_db);
		for(i=0;i<P_SIZE;i++)
		{
			MEM[block_us+i] = buff[i];
		}
		
		BLOCKS[block_us] = page_table;
		BLOCKS_T[block_us] = FCFS;
		FCFS++;
		block_used++;
		sim_db->ptable[page_table].frame = MMEM;
		sim_db->ptable[page_table].valid = 1;
		return(buff[offset]);
	}
	printf("Data is : %s \n", buff);
	
	return('a');
}
//=============================================================================
int vm_store(sim_database *sim_db,unsigned short virtual_addr,
						unsigned char value)
{
	//	HUY ZNAET CHTO
	unsigned short offset =	virtual_addr & 15;
	unsigned short page_table = virtual_addr>>4 ;
	
	if(sim_db->ptable[page_table].permission == 0)
	{
		//printf("Cannot write to closed memory\n");
		return(-1);
	}
	if(sim_db->ptable[page_table].valid == 1)
	{	//	In main memory
		MEM[offset] = value;
	}
	else if(sim_db->ptable[page_table].valid == 0)
	{
		if(sim_db->ptable[page_table].frame == SWAP)
		{	//	Go to SWAP			
			sim_db->ptable[page_table].touched = 1;	
		}
		else if(sim_db->ptable[page_table].frame == HARD)
		{	//	Go to HARD
			sim_db->ptable[page_table].touched = 1;
		}		
	}
	
	return(0);
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
	
	sim_database *sim_db=vm_constructor(EXEC_FILE,TEXT_SIZE,DATA_SIZE,BSS_SIZE);
	int i;
	unsigned short addr;
	unsigned char val ;
	for(i=0;i<LOOPS;i++)
	{
		addr =rand()%EXEC_SIZE;
		val = vm_load(sim_db,addr);
		val = rand()%DIFF +LETTER_START;
		vm_store(sim_db,addr+1,val);
	
	}
	
	vm_print(sim_db);
	vm_destructor(sim_db);
		
	return(EXIT_SUCCESS);
	
}



//=============================================================================
//=============================================================================
//=============================================================================









