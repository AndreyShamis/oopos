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

#define LOOPS 900


#define EXEC_SIZE 1024
#define PAGE_NUM 64
#define P_SIZE 16
#define FRAME_NUM 4
#define PHISYCAL_MEM_SIZE 64

#define TEXT_R 	0
#define DATA_R 	1
#define BSS_R	2
#define HEAP_R  3
//=============================================================================



char 			MEM[PHISYCAL_MEM_SIZE];	//	memory
int 			BLOCKS[FRAME_NUM];		//	frames
unsigned int 	BLOCKS_T[FRAME_NUM];	//	timers peer frame
int 			block_used;				//	counter of used frames
unsigned int 	FCFS = 0;				//	virtual timer in simulation
//=============================================================================


typedef struct stats_struct
{
	unsigned int page_faults;
	unsigned int swap_outs;
	unsigned int bring_swap;
	unsigned int bring_hard;
	unsigned int hits;
	
}stats_struct;

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

	stats_struct stats;

short int getFreeBlock(sim_database *sim_db);

void vm_destructor(sim_database *sim_db);

sim_database *vm_constructor(char *executable,const unsigned short text,
const unsigned short data,const unsigned short bss);

void swap_out(sim_database *sim_db,
						const short int table,const short int block);

char vm_load(sim_database *sim_db,const unsigned short virtual_addr);

int vm_store(sim_database *sim_db,const unsigned short virtual_addr,
						const unsigned char value);
						



int vm_print(sim_database *sim_db)
{
	
	printf("\t# Swap descriptor %d.\t",sim_db->swap_fd);
	printf("File descriptor %d.\n",sim_db->program_fd);
	printf("\t# Swap outed:%d.\t",stats.swap_outs);
	printf("Hits:%d.\t Page fault:%d.\t",stats.hits,stats.page_faults);
	printf("Swap hit:%d.\t HDD hit:%d.\n",stats.bring_swap,stats.bring_hard);
	
	int i,j;
	printf("==========================MEMORY==========================\n");
	for(i=0;i<FRAME_NUM;i++)
	{
		printf("Frame[%d]:",i);
		for(j=0;j<P_SIZE;j++)
		{
			printf("%c",MEM[i*P_SIZE+j]);
		}
		printf("\n");
	
	}
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
		addr = rand()%EXEC_SIZE;
		val = vm_load(sim_db,addr);
		val = rand()%DIFF +LETTER_START;
		vm_store(sim_db,addr+1,val);
	
	}
	
	vm_print(sim_db);
	vm_destructor(sim_db);
		
	return(EXIT_SUCCESS);
	
}

//=============================================================================
//	Function which get pointer to data base of memory , adress which gona be 
//	changed and value - new value of spec adress
//	return -1 on error ; 0 - on success
int vm_store(sim_database *sim_db,const unsigned short virtual_addr,
						const unsigned char value)
{
	unsigned short offset =	virtual_addr & 15;		//	offset variable
	unsigned short page_table = virtual_addr>>4 ;	//	page number
	
	//	Check if can write into this page
	if(sim_db->ptable[page_table].permission == 0)
		return(-1);		//	return error
	
	//	Check if the page located in memory , if not bring him
	if(sim_db->ptable[page_table].valid == 0)
	{
			vm_load(sim_db,virtual_addr);
			sim_db->ptable[page_table].touched = 1;		//	chenge touched
	}
	
	//	Change the value in memory of spec adress
	MEM[offset+ sim_db->ptable[page_table].frame*P_SIZE] = value;
	
	return(0);			//	return success

}

//=============================================================================
//	Function destructor. Clear all used memory, close used files.
void vm_destructor(sim_database *sim_db)
{

	close(sim_db->swap_fd);			//	close swap file
	close(sim_db->program_fd);		//	close program file
	
	free(sim_db->swap_file);		//	clear allocated memory
	free(sim_db->ptable);			//	clear allocated memory
	free(sim_db);					//	clear allocated memory
}

//=============================================================================
//	Program simulation constructor.
//	This funcion get pointer to file name fich need "run", size of text blick
//	size of data and size of bss.
//	Return the struct which provide the main data dase structure
sim_database *vm_constructor(char *executable,const unsigned short text,
const unsigned short data,const unsigned short bss)
{
	int count = 0;					//	work variable
	short int section = TEXT_R;		//	indicator variable

	for(count=0;count<FRAME_NUM;count++)
	{
		BLOCKS[count] 	= 0;		//	set used in simulation variables
		BLOCKS_T[count] = 0;		//	set used in simulation variables	
	}
	
	block_used = 0;					//	set used in simulation variables
	//	Craete and set ptable
	sim_database *ret=NULL;		
	//	Allcocate memory for main data base
	ret = (sim_database *) malloc(sizeof(sim_database));
	
	//	Allocate memory for page table
	ret->ptable = (page_descriptor *) malloc(PAGE_NUM*sizeof(page_descriptor)); 
	ret->swap_file = (char *)malloc(strlen(SWAP_FILE)*sizeof(char)+1);
		
	//	Check if allocated
	if(ret == NULL || ret->ptable == NULL || ret->swap_file == NULL)
	{
		perror("Cannot allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	//	Open SWAP file in correct size
	
	strcpy(ret->swap_file,SWAP_FILE);
	ret->swap_fd 	= open(ret->swap_file,O_CREAT | O_RDWR | O_TRUNC);
	
	//	Open program file
	ret->program_fd 	= open(executable,O_RDONLY);//| O_CREAT
	ret->program_file = executable;
		

	for(count=0;count<PAGE_NUM;count++)
	{
		if(count*P_SIZE > TEXT_SIZE && section == 0)
			section=DATA_R;
		else if(count*P_SIZE > TEXT_SIZE +DATA_SIZE && section == 1)
			section = BSS_R;
		else if(count*P_SIZE > TEXT_SIZE+DATA_SIZE+BSS_SIZE && section == 2)
			section=HEAP_R;		
		
		ret->ptable[count].valid 		= 0;
		if(section == HEAP_R || section == BSS_R || section == DATA_R)
			ret->ptable[count].permission 	= 1;
		else
			ret->ptable[count].permission 	= 0;
			
		ret->ptable[count].touched 		= 0;
		ret->ptable[count].frame 		= -1;
	}
	
	return(ret);
}

//=============================================================================
//	Function which get 
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
		//printf("2 - Table %d . Block: %d\n", table,block);
		lseek(sim_db->swap_fd,table*P_SIZE-TEXT_SIZE-DATA_SIZE,SEEK_SET);
		write(sim_db->swap_fd,buff,P_SIZE);	
		sim_db->ptable[table].frame = 0;
		sim_db->ptable[table].valid = 0;
		stats.swap_outs++;
	}
	else
	{
		sim_db->ptable[table].frame = -1;
		sim_db->ptable[table].valid = 0;	
	
	}
	block_used--;
}
//=============================================================================
short int getFreeBlock(sim_database *sim_db)
{
	int i = 0;
	short int block_f=BLOCKS_T[0];
	unsigned int tm=-1;
	
	if(block_used < 4)
	{
		for(i=0;i<4;i++)
			if(BLOCKS[i] == 0)
				return(i);
	}
	else
	{
		for(i=0;i<4;i++)
		{
			if(BLOCKS_T[i] < tm)
			{
				tm = BLOCKS_T[i];
				block_f = i;
			}
		}

		swap_out(sim_db,BLOCKS[block_f],block_f);
		stats.swap_outs++;

		return(block_f);

	}
	
	return(0);

}

//=============================================================================
char vm_load(sim_database *sim_db,const unsigned short virtual_addr)
{
	
	unsigned short offset =	virtual_addr & 15;		//	offset of mem
	unsigned short page_table = virtual_addr>>4 ;	//	page table
	char buff[P_SIZE];								//	Buffer for reading
	int i=0;										//	work variable
	short int frame_id =	0;						//	new frame id

	if(virtual_addr >1024)
		printf("Big memory adress request : %d\n", virtual_addr);

	//	Check if the page located in main memory	
	if(sim_db->ptable[page_table].valid == 1)
	{	//	In main memory
		stats.hits++;
		return(MEM[offset+ sim_db->ptable[page_table].frame*P_SIZE]);
		
	}
	//	if page not located in main memory bring from actual place
	else if(sim_db->ptable[page_table].valid == 0)
	{
		stats.page_faults++;
		//	bring the page from swap section
		if(sim_db->ptable[page_table].frame == 0)
		{
			stats.bring_swap++;
			lseek(sim_db->swap_fd,page_table*P_SIZE,SEEK_SET);
			read(sim_db->swap_fd, buff,P_SIZE);	
		}
		//	bring the page from hard disk 
		else if(sim_db->ptable[page_table].frame == -1)
		{
			stats.bring_hard++;	
			lseek(sim_db->program_fd,page_table*P_SIZE,SEEK_SET);
			read(sim_db->program_fd, buff,P_SIZE);		
		}
		
		frame_id = getFreeBlock(sim_db);	//	get new frame id
		
		for(i=0;i<P_SIZE;i++)
			MEM[frame_id+i] = buff[i];		//	Copy page to memory
		
		BLOCKS[frame_id] 	= page_table;	//	set id frame the page located
		BLOCKS_T[frame_id] 	= FCFS;			//	set the virt time the page load
		FCFS++;								//	Update ritual time
		block_used++;						//	Update frame counter
		
		sim_db->ptable[page_table].frame = frame_id;// update page location
		sim_db->ptable[page_table].valid = 1;		// update mem location
		return(buff[offset]);						// return the value
	}
	
	return('0');
}


//=============================================================================
//=============================================================================
//=============================================================================









