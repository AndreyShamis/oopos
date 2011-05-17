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
#define EXE_FILE "exec"
#define SWAP_FILE "swap_file"

#define LOOPS 700

#define FILE_CHMOD 0600

#define EXEC_SIZE 1024
#define PAGE_NUM 64
#define P_SIZE 16
#define FRAME_NUM 4
#define PHISYCAL_MEM_SIZE 64

#define TEXT_R 	0
#define DATA_R 	1
#define BSS_R	2
#define HEAP_R  3

#define OFFSET_PREF 15
#define ADRESS_PREF 4
//=============================================================================



char 			MEM[PHISYCAL_MEM_SIZE];	//	memory
int 			BLOCKS[FRAME_NUM];		//	frames
unsigned int 	BLOCKS_T[FRAME_NUM];	//	timers peer frame
int 			block_used=0;				//	counter of used frames
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
	int valid;
	int permission;
	int touched;
	int frame;
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
						
void CheckIfFileOpened(const int fd,sim_database *sim_db);

void vm_print(sim_database *sim_db);

sim_database *MemoryAllocating();

void FilePreparing(sim_database *ret,char *executable);

void CheckIOSuccess(const int value,sim_database *sim_db);
