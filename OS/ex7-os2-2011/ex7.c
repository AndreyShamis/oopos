//=============================================================================
//	Students 
//				Andrey Shamis		321470882, login: andreysh
//				Ilia Gaysinsky		309480051, login: iliaga
/*

	This program provide tools for manipulations with virtual memory
	
	For compile just run:
		
		make
		
	for run the program use next comand line
		
		./ex7
		
	The Directory must have file exec.
	And after runing the program file directory get new file called
	swap_file

*/
//=============================================================================
#include "ex7.h"

//=============================================================================
int main()
{

	srand(time(NULL));
	
	//	Construct the data base
	sim_database *sim_db=vm_constructor(EXE_FILE,TEXT_SIZE,DATA_SIZE,BSS_SIZE);
	int count;							//	counter for cyccle
	unsigned short addr;				//	work adress
	unsigned char val ;					//	value for char
	for(count=0;count<LOOPS;count++)
	{
		addr = rand()%(EXEC_SIZE);	
		val = vm_load(sim_db,addr);
		val = rand()%DIFF +LETTER_START;
		vm_store(sim_db,addr+1,val);
	
	}
	
	vm_print(sim_db);			//	print statistic
	vm_destructor(sim_db);		//	destruct used data
		
	return(EXIT_SUCCESS);		//	exit
	
}
//=============================================================================
//	Function which looking for clean and get grame for same page.
//	Getting pointer to main data base structure
//	Return the actual id of free frame in memory
short int getFreeBlock(sim_database *sim_db)
{
	int 		count 	= 0;			//	work variable
	short int block_f	= BLOCKS_T[0];	//	return value
	unsigned int tm		= -1;			//	temporary variable
	
	//	if still have free frame
	if(block_used < FRAME_NUM)
	{
		for(count=0;count<FRAME_NUM;count++)
			if(BLOCKS[count] == 0)
				return(count);
	}
	else
	{
		//	if need to find new place
		//	Start looking for frame which was used in last time 	
		for(count=0;count<FRAME_NUM;count++)
		{
			//	compare between values
			if(BLOCKS_T[count] < tm)
			{
				//	tring to get smallest valuer
				tm = BLOCKS_T[count];	//	update temp var
				block_f = count;		//	set the id of frame founded
			}
		}

		swap_out(sim_db,BLOCKS[block_f],block_f);
		stats.swap_outs++;				//	update statistic

		return(block_f);
	}
	
	return(0);

}

//=============================================================================
//	Function which allocate needed memory for simulation
//	Return pointer to main data base structure
sim_database *MemoryAllocating()
{
	//	set used in simulation variables
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
	
	return(ret);
}

//=============================================================================
//	Function which checking if file readed or writed.
//	Geting value which function read or write return and pointer to main
//	data base structure
void CheckIOSuccess(const int value,sim_database *sim_db)
{
	if(value == -1)
	{
		vm_destructor(sim_db);				//	call destructor
		perror("Can not write into file\n");	//	print error
		exit(EXIT_FAILURE);					//	exit
	}
}

//=============================================================================
//	FUnction for print information about simulation
//	Get pointer to main data base structure
void vm_print(sim_database *sim_db)
{
	int i,j;			//	Used variables
	
	printf("\t# Swap descriptor %d.\t",sim_db->swap_fd);
	printf("File descriptor %d.\n",sim_db->program_fd);
	printf("\t# Swap outed:%d.\t",stats.swap_outs);
	printf("Hits:%d.\t Page fault:%d.\t",stats.hits,stats.page_faults);
	printf("Swap hit:%d.\t HDD hit:%d.\n",stats.bring_swap,stats.bring_hard);		
	printf("==========================MEMORY==========================\n");
	
	for(i=0;i<FRAME_NUM;i++)
	{
		printf("Frame[%d]:",i);				//	Print each frame in memory
		for(j=0;j<P_SIZE;j++)
		{
			printf("%c",MEM[i*P_SIZE+j]);	//	Print each char in frame
		}
		printf("\n");						//	new line
	
	}
	
	printf("pID\tValid\tPerm\tTouch\tFrame\n");
	//	Print page table content
	for(i=0;i<PAGE_NUM;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\n",i,sim_db->ptable[i].valid,
			sim_db->ptable[i].permission,sim_db->ptable[i].touched,
			sim_db->ptable[i].frame);
		
	}

}

//=============================================================================
//	Function which get pointer to main data base structure
//	table id and block id.
//	Do swap out some frame from memory to independ of changed or not - 
//	HDD or swap space
void swap_out(sim_database *sim_db,const short int table,const short int block)
{
	char buff[P_SIZE];					//	temp variable
	int i = 0;							//	cycle variable
	
	//	If page was changes save him
	if(sim_db->ptable[table].touched )
	{
		int goBack = TEXT_SIZE+DATA_SIZE;			//	unset in swap file
		//	Copy page to buffer for save it to swap file
		for(i=0;i<P_SIZE;i++)
			buff[i] = MEM[block*P_SIZE+i];  		//	copy
		
		//	saving it
		sim_db->ptable[table].frame = table*P_SIZE-goBack;
		lseek(sim_db->swap_fd,sim_db->ptable[table].frame,SEEK_SET);
		//	writing to swap
		CheckIOSuccess(write(sim_db->swap_fd,buff,P_SIZE),sim_db);	
		sim_db->ptable[table].valid = 0;
		stats.swap_outs++;							//	update statistic
	}
	else
	{
		//	if page not chabges just update data
		sim_db->ptable[table].frame = -1;			//	on hard
		sim_db->ptable[table].valid = 0;			//	not in memory
	}
	
	block_used--;							//	decrease frames counter

}

//=============================================================================
//	Function which get pointer to data base of memory , adress which gona be 
//	changed and value - new value of spec adress
//	return -1 on error ; 0 - on success
int vm_store(sim_database *sim_db,const unsigned short virtual_addr,
						const unsigned char value)
{
	unsigned short offset =	virtual_addr & OFFSET_PREF;		//	offset variable
	unsigned short page_table = virtual_addr>>ADRESS_PREF;	//	page number
	
	//	Check if can write into this page
	if(sim_db->ptable[page_table].permission == 0 || virtual_addr>=EXEC_SIZE)
		return(-1);		//	return error
	
	//	Check if the page located in memory , if not bring him
	if(sim_db->ptable[page_table].valid == 0)
	{
			vm_load(sim_db,virtual_addr);
			sim_db->ptable[page_table].touched = 1;	//	chenge touched
	}
	
	//	Change the value in memory of spec adress
	MEM[offset+ sim_db->ptable[page_table].frame*P_SIZE] = value;
	
	return(0);										//	return success

}

//=============================================================================
//	Function destructor. Clear all used memory, close used files.
void vm_destructor(sim_database *sim_db)
{

	close(sim_db->swap_fd);						//	close swap file
	close(sim_db->program_fd);					//	close program file
	
	free(sim_db->swap_file);					//	clear allocated memory
	free(sim_db->ptable);						//	clear allocated memory
	free(sim_db);								//	clear allocated memory
}

//=============================================================================
//	Function for preparing files which needed in program simulation
//	Geting pointer to main data base structure nd also get file name of hdd
void FilePreparing(sim_database *ret,char *executable)
{
	//	Open SWAP file in correct size
	strcpy(ret->swap_file,SWAP_FILE);
	ret->swap_fd	=	creat(ret->swap_file,FILE_CHMOD);
	ret->swap_fd 	= open(ret->swap_file,O_RDWR | O_CREAT);
	CheckIfFileOpened(ret->swap_fd,ret);	//	check fd
	
	//	Open program file
	ret->program_fd 	= open(executable,O_RDONLY);//| O_CREAT
	ret->program_file = executable;
	CheckIfFileOpened(ret->program_fd,ret);	//	check fd

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
	
	sim_database *ret = MemoryAllocating();	//	allocate needed memory
	
	FilePreparing(ret,executable);		//	preparinf files
	
	for(count=0;count<PAGE_NUM;count++)
	{
		if(count*P_SIZE >= TEXT_SIZE && section == 0)
			section=DATA_R;
		else if(count*P_SIZE >= TEXT_SIZE +DATA_SIZE && section == 1)
			section = BSS_R;
		else if(count*P_SIZE >= TEXT_SIZE+DATA_SIZE+BSS_SIZE && section == 2)
			section=HEAP_R;		
		
		ret->ptable[count].valid 		= 0;
		if(section == HEAP_R || section == BSS_R)// || section == DATA_R
			ret->ptable[count].permission 	= 1;
		else
			ret->ptable[count].permission 	= 0;
			
		ret->ptable[count].touched 		= 0;
		ret->ptable[count].frame 		= -1;
	}
	
	return(ret);
}


//=============================================================================
//	Load function - function which checking if adress value loaded to main
//	memory if yes return value if not trying to load the page from 
//	file - independ - swap / hdd
//	Get pointer to main structure adata base and the virtual adress
char vm_load(sim_database *sim_db,const unsigned short virtual_addr)
{
	
	unsigned short offset =	virtual_addr & OFFSET_PREF;		//	offset of mem
	unsigned short page_table = virtual_addr>>ADRESS_PREF;	//	page table
	char buff[P_SIZE];								//	Buffer for reading
	int i=0;										//	work variable
	short int frame_id =	0;						//	new frame id

	if(virtual_addr >=EXEC_SIZE)
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

		if(sim_db->ptable[page_table].frame >= 0)
		{
			stats.bring_swap++;
			lseek(sim_db->swap_fd,sim_db->ptable[page_table].frame,SEEK_SET);
			CheckIOSuccess(read(sim_db->swap_fd, &buff,P_SIZE),sim_db);
		}
		//	bring the page from hard disk 
		else if(sim_db->ptable[page_table].frame == -1)
		{
			stats.bring_hard++;	
			lseek(sim_db->program_fd,page_table*P_SIZE,SEEK_SET);
			CheckIOSuccess(read(sim_db->program_fd, &buff,P_SIZE),sim_db);		
		}
		
		frame_id = getFreeBlock(sim_db);	//	get new frame id
		
		for(i=0;i<P_SIZE;i++)
			MEM[frame_id*P_SIZE+i] = buff[i];		//	Copy page to memory
		
		
		BLOCKS[frame_id] 	= page_table;	//	set id frame the page located
		BLOCKS_T[frame_id] 	= FCFS;			//	set the virt time the page load
		FCFS++;								//	Update ritual time
		block_used++;						//	Update frame counter
		
		sim_db->ptable[page_table].frame = frame_id;// update page location
		sim_db->ptable[page_table].valid = 1;		// update mem location
		return(buff[offset]);						// return the value
	}
	
	return('0');							//	for compiler return
}

//=============================================================================
//	Function which cheking if file descriptor is good
//	on error exot from program
void CheckIfFileOpened(const int fd,sim_database *sim_db)
{
	//	check
	if(fd == -1)
	{
		vm_destructor(sim_db);				//	call destructor
		perror("Can not open file\n");	//	print error
		exit(EXIT_FAILURE);					//	exit
	}	
}

//=============================================================================
//=============================================================================
//=============================================================================
