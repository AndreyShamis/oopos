/*
 * 	This file provide header file for main program
 * Which provide tools for simulation of work wich file system
 * in computer.
 *
 */

#ifndef _EX9			//	Define Header Off ex9
#define _EX9
//=============================================================================
//	Include Section
#include <stdio.h>		//	standrard I/O
#include <stdlib.h>		//	used for EXIT_SUCCESS
#include <string.h>		//	used in strlen
#include <unistd.h>
#include <math.h>		//	posible for use in pow

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>	//	for use mmap function
#include <fcntl.h>
//=============================================================================
//	Define section

#define FILENAME "testFS.dat"		//	file system file
#define ROOT_DIRECTORY_HANDLE 0 // 	the root ('/') dir handle

#define ROOT_DIR_NAME "/"

#define BLOCK_SIZE 16				//	size of block
#define BLOCK_ADSRESS_SIZE 4		//	blovk adress size

#define MAX_FILE_NAME 12			//	max file name size

#define DIRECT_ENTRIES 3
#define SINGLE_INDIRECT_ENTRIES 1	//	variable
#define DOUBLE_INDIRECT_ENTRIES 1	//	variable

#define ENTRIES_PER_BLOCK (BLOCK_SIZE/BLOCK_ADSRESS_SIZE)

#define NR_BLOCKS 3712				//	number of blocks
#define NR_INODES 128				//	number of inodes

//	maximum blocks held by the single/double indirect entries
#define SINGLE_INDIRECT_BLCOKS ENTRIES_PER_BLOCK
#define DOUBLE_INDIRECT_BLOCKS (ENTRIES_PER_BLOCK*ENTRIES_PER_BLOCK)

//	maximum blocks an inode can hold
#define BLOCKS_PER_INODE (DIRECT_ENTRIES \
				+ SINGLE_INDIRECT_ENTRIES*SINGLE_INDIRECT_BLCOKS \
				+ DOUBLE_INDIRECT_ENTRIES*DOUBLE_INDIRECT_BLOCKS)

//	maximum file size in bytes
#define MAX_FILE_SIZE (BLOCKS_PER_INODE*BLOCK_SIZE)

//	number of bits per block
#define BLOCK_BITS (BLOCK_SIZE*sizeof(char))
#define NODE_SIZE sizeof(struct FSInode)

#define DATA_START (NR_BLOCKS+(NR_INODES*NODE_SIZE))
#define DEC_DEV 10			//	devider used in converting int tostring


//#define _DEBUG 1					//	Uncomment this for see debug messages
//#define _DEBUG_WRITE 1
//#define _SHOW_STATISTIC 1			//	Comment this if you dont need statistic
//=============================================================================


struct DirEntry
{
	char 	filename[MAX_FILE_NAME];
	int 	inode;
};

struct FSInode
{
	int 	inUse;								//	Tell as if file in use
	int 	fileSize;							//	File size
	int 	directBlocks[DIRECT_ENTRIES];		//	Pointer to 3 first blocks
	int 	singleIndirectBlocks[SINGLE_INDIRECT_ENTRIES];
	int 	doubleIndirectBlocks[DOUBLE_INDIRECT_ENTRIES];
};

struct FileDescriptor
{
	int 	inUse;
	int 	fd;
	char 	filename[MAX_FILE_NAME];
	int 	inode;
	int		fileOffset;
};

struct fs
{

	int Bitmap[NR_BLOCKS];				//	Tell us which blocks are occupaied
	struct FSInode inodeList[NR_INODES];//	map the inodes on the disk.

	//	pointer to the first Inode (the first directory)
	struct FSInode *pRootInode;
	struct FileDescriptor fileTable[NR_INODES];//	holds the open FileDesc

	int fsInitialized;				//	=0 if initializes,i otherwise
	int fd;							//	fd of our virtual HSS - //FILE *fd;

	char 	*source;		//	maped array for Bitmap and Indoe Section
	size_t 	filesize;		//	size of mapped file

};

typedef struct fs fs_t;

//=============================================================================
/*		Function which serach in struct which Inode not in use.
 * 	Geting pointer to main data base structure.
 * Return n>0 if finded somthing ot -1 if not */
int findNotUsedIndoe(fs_t *fs);
//=============================================================================
/*		Function wich looking in main data base wich bitmap is in not use.
 * 		Get pointer to main data base.
 * 		Return n>=0 if found; -1 if not found*/
int findNotUsedBitMap(fs_t *fs);
//=============================================================================
/*		Function for convert char(string) to int
 * 	Geting String wich need convert and pointer to int in wich be returned
 * 	the value. */
void forCharsToInt(char val[BLOCK_ADSRESS_SIZE],int *retValue);
//=============================================================================
/*		Function for convert int to char
 * 	Geting integer wich need convert and char in wich be retuned
 * converted value*/
void intToChar(char val[BLOCK_ADSRESS_SIZE],const int valInt);
//=============================================================================
/*
 * 		Function wich read from file into buffer
 * 	Getting file description , size of bytes need to read, pointer to data
 * 	structure.
 * 		Return in buffer pointer string readed, and returned value it is
 * 	size of readed bytes*/
int fsReadFile(fs_t *fs,int fd,char *buffer,int readSize);
//=============================================================================
/*
 * 		Function for reading only one block each call
 * 	Function geting pointer to data structure wich used in our program,
 * 	File discriptor of file wich we wont to read, and buffer.
 * 		Return: funvtion return in buffer pointer the information readed
 * 	from block, and also return the size wich was readed, usualy it
 * 	is BLOCK_SIZE but if not success to read- it is happen where trying
 * 	to read more then file have so return 0 or on error -1*/
int fsReadFileBlock(fs_t *fs,int fd,char *buffer);
//=============================================================================
/*
 * 		Function wich print statistic about program simulation.
 * 	Get pointer to main data base.
 *
 * 	Print information such:
 * 	-	Status of bitmap usage
 * 	-	Files in directory(we have only one)
 * 	-	Size of each file
 * 	-	And list of block for each file*/
void PrintStatistic(fs_t *fs);


void PrepareAllInodesOnMount(fs_t *fs);
void SaveToFS_BitMap_INODES(fs_t *fs);

//=============================================================================
/*
 *
 */
int fsFormat(fs_t *fs)
{
	//lseek(fs->fd,66688,SEEK_SET);
	//write(fs->fd,"-",1);

		#ifdef _DEBUG
		printf("#Start formating\n");
		#endif
	int coun = 0;
 	coun = 0;

	for(coun=0;coun<NR_BLOCKS;coun++)
	{
		//printf("Write to bitmap\n");
		fs->Bitmap[coun] = 0;

	}
//	for(coun=NR_BLOCKS;coun<DATA_START;coun++)
//	{
//		//printf("Write to bitmap\n");
//		fs->Bitmap[coun] = 'A';
//
//	}
	for(coun=0;coun<NR_INODES;coun++)
	{
		fs->inodeList[coun].inUse 		= 0;
		fs->inodeList[coun].fileSize 	= 0;
		fs->inodeList[coun].directBlocks[0] = 0;
		fs->inodeList[coun].directBlocks[1] = 0;
		fs->inodeList[coun].directBlocks[2] = 0;
		fs->inodeList[coun].singleIndirectBlocks[0] = 0;
		fs->inodeList[coun].doubleIndirectBlocks[0] = 0;

	}
 	//fs->inodeList[0] =
	fs->pRootInode = &fs->inodeList[ROOT_DIRECTORY_HANDLE];
	fs->pRootInode->inUse = 1;
	fs->fileTable[ROOT_DIRECTORY_HANDLE].inode = ROOT_DIRECTORY_HANDLE;
	fs->fileTable[ROOT_DIRECTORY_HANDLE].fileOffset =0 ;


	fs->fsInitialized = 1;
	SaveToFS_BitMap_INODES(fs);

	lseek(fs->fd,DATA_START,SEEK_SET);

	char tmpBuffer[BLOCK_SIZE];

	memset(tmpBuffer,'-',BLOCK_SIZE);

	int res= 0;
	for(coun = 0 ; coun < NR_BLOCKS;coun++)
	{

		res= write(fs->fd,tmpBuffer,BLOCK_SIZE);

		if(res < 0)
		{
			printf("Cant write. Iteration num: %d\n",coun);
		}

	}
	PrepareAllInodesOnMount(fs);

	return(0);

}
//=============================================================================
/*
 *
 */
void PrepareAllInodesOnMount(fs_t *fs)
{
	int coun = 0;

	#ifdef _DEBUG
	printf("TODO:?Preparing to set memory for inodes\n");
	#endif
	int fsReadFileBlock(fs_t *fs,int fd,char *buffer);
	/*for(coun=0;coun<NR_INODES;coun++)
	{
		fs->inodeList[coun].inUse 		= 0;
		fs->inodeList[coun].fileSize 	= 0;


	}*/

	int temp=0;
	char buffer[sizeof(struct FSInode)];

	for(coun = 0 ; coun < NR_INODES;coun++)
	{

		for(temp = 0;temp < NODE_SIZE;temp++)
		{
			buffer[temp] = fs->source[NR_BLOCKS+coun*NODE_SIZE + temp];
		}
		memcpy(&fs->inodeList[coun],buffer,NODE_SIZE);
		//memmove
		fs->fileTable[coun].inUse = 0;
		fs->fileTable[coun].fileOffset = 0;
		fs->fileTable[coun].fd = 0;
		fs->fileTable[coun].inode = 0;

	}
}

void SaveToFS_BitMap_INODES(fs_t *fs)
{
	int coun = 0;
	char temp = '\0';

	for(coun=0;coun<NR_BLOCKS;coun++)
	{
		temp = fs->Bitmap[coun] + '0';
		//printf("Save char: {%c}.Digit:{%d}.\n",temp,temp);
		fs->source[coun]= temp;

	}


	int tempI=0;
	char buffer[sizeof(struct FSInode)];

	for(coun = 0 ; coun < NR_INODES;coun++)
	{
		memcpy(buffer,&fs->inodeList[coun],NODE_SIZE);

		for(tempI = 0;tempI < NODE_SIZE;tempI++)
		{
			fs->source[NR_BLOCKS+coun*NODE_SIZE + tempI] = buffer[tempI];
		}

	}
}
//=============================================================================
/*
 *
 */
fs_t *fsMount()
{
	fs_t *ret = NULL;

	ret = (fs_t*)malloc(sizeof(fs_t));
	if(ret == NULL)
	{
		perror("Can not  allocate memory in fsMount\n");
		exit(EXIT_FAILURE);
	}

	//creat(filename,0600);
	ret->fd = open(FILENAME,O_RDWR | O_CREAT);
	if(ret->fd == -1)
	{
		perror("Cannot open simulation file.\n");
		exit(EXIT_FAILURE);
	}

	//SEEK-SET
	ret->filesize = lseek(ret->fd,DATA_START,SEEK_SET);

	ret->source = mmap(0,ret->filesize,
			PROT_READ|PROT_WRITE,MAP_SHARED,ret->fd,0);
 	if(ret->source == (char *) -1)
 	{
  		perror("Can not open map file\n");
 		//vm_destructor(ret);				//	call destructor
		exit(EXIT_FAILURE);					//	exit

  	}

 	int coun = 0;

 	#ifdef _DEBUG
 	printf("Size located %d and size of NR_BLOCKS %d.\n",
 			ret->filesize, NR_BLOCKS);
	#endif

 	for(coun=0;coun<NR_BLOCKS;coun++)
	{
		ret->Bitmap[coun] = ret->source[coun]- '0';

	}

	PrepareAllInodesOnMount(ret);


	memcpy(&ret->fileTable[ROOT_DIRECTORY_HANDLE].filename,ROOT_DIR_NAME,sizeof(ROOT_DIR_NAME));

	ret->fileTable[ROOT_DIRECTORY_HANDLE].inUse = 1;
	ret->fileTable[ROOT_DIRECTORY_HANDLE].inode = ROOT_DIRECTORY_HANDLE;
	ret->fileTable[ROOT_DIRECTORY_HANDLE].fd = 0;
	ret->fileTable[ROOT_DIRECTORY_HANDLE].fileOffset = ret->inodeList[ROOT_DIRECTORY_HANDLE].fileSize;

	ret->fsInitialized = 1;		//	TODO

	return(ret);
}


//=============================================================================
/*
 *
 */
int fsUnMount(fs_t *fs)
{
	#ifdef _DEBUG
	printf("TODO:+Start UnMount file system.\n"
			"TODO:+Start write Bitmap to mmap.\n");

	#endif


	SaveToFS_BitMap_INODES(fs);

	#ifdef _DEBUG
	printf("TODO:Try unmap\n");
	#endif
	if(munmap(fs->source, fs->filesize) == -1)
		perror("Error un-mmapping the file\n");

	close(fs->fd);
	free(fs);
	return(0);
}

int AllocateBlock(fs_t *fs)
{
	int ret_val = findNotUsedBitMap(fs);

	if(ret_val>=0)
	{
		fs->Bitmap[ret_val] = 1;
		return(ret_val);
	}

	return(-1);
}
//	Blcok of CREATE/OPEN/CLOSE
//=============================================================================
/*
 *
 */
int fsCreateFile(fs_t *fs,char *fileName)
{
	int coun = 0;							//	temp variable
	int freeBMres=0;						//	temp var for free BitMap bit
	struct DirEntry newFile;				//	Struct for new file

	int ret_FD = 0;
	#ifdef _DEBUG
	printf("TODO:?Start create file\n");
	#endif


	if(sizeof(fileName) >= MAX_FILE_NAME)
	{
		return(-1);
	}

	char newFileName[MAX_FILE_NAME];

	memset(newFileName,'+',MAX_FILE_NAME);	//
	strcpy(newFileName,fileName);			//	DONT CHANGE TO MEMCPY.
	//	This function put \0 on right space




	if(fs->fsInitialized)
	{
		int newIndoeID = findNotUsedIndoe(fs);	//	get free inode

			//printf("Free inode founded %d\n",newIndoeID);
			#ifdef _DEBUG
			printf("TODO:?Trying find free Inode\n");
			#endif
		//	Check if indoe was returned is good
		if(newIndoeID>=0)
		{

				#ifdef _DEBUG
				printf("TODO:?Trying find free bitmap\n");
				#endif



				for(coun = 1; coun <NR_INODES;coun++)
				{
					if(fs->fileTable[coun].inUse == 0)
					{
						ret_FD = coun;
						break;
					}
				}

			//	printf("File descriptor founded %d\n",ret_FD);
				//	Set name
				memcpy(&newFile.filename,newFileName,MAX_FILE_NAME);
				newFile.inode = newIndoeID;		//	set Inode id

				char buffer[MAX_FILE_NAME + BLOCK_ADSRESS_SIZE];

				//	Preparing write data to file (Direcroty)
				memcpy(buffer,&newFile,MAX_FILE_NAME + BLOCK_ADSRESS_SIZE);
				fsWriteFile(fs,ROOT_DIRECTORY_HANDLE,buffer,sizeof(buffer));
/*
			for(coun = 0 ;coun<DIRECT_ENTRIES;coun++)
			{
				freeBMres=findNotUsedBitMap(fs);
				if(freeBMres>=0)
				{
					fs->inodeList[newIndoeID].directBlocks[coun] = freeBMres;
					fs->Bitmap[freeBMres] = 1;
				}
				else
				{
					printf("TODO:-Cant get free bitMap\n");
					return(freeBMres);
				}
			}
*/
			fs->inodeList[newIndoeID].inUse = 1;
			fs->fileTable[ret_FD].inUse = 1;
			fs->fileTable[ret_FD].fd = ret_FD;
			fs->fileTable[ret_FD].inode = newIndoeID;


		}
		else
		{
			#ifdef _DEBUG
			printf("TODO:-All Indoes used. Can`t create file!\n");
			#endif
			return(newIndoeID);
		}
			#ifdef _DEBUG
			printf("TODO:+Success create file\n");
			#endif

		return(ret_FD);
			//		return(newIndoeID);
	}
	else
	{
		#ifdef _DEBUG
		printf("TODO:-Canot create file %s, you need format file system.\n",
				fileName);
		#endif
		return(-1);

	}
}
//=============================================================================
/*
 *
 */
int fsOpenFile(fs_t *fs,char *fileName)
{
#ifdef _DEBUG
	printf(" - Start open file. File name: %s\n",fileName);
#endif

#ifdef _DEBUG
	printf(" - End open file.\n");
#endif
	return(0);
}
//=============================================================================
/*
 *
 */
int fsCloseFile(fs_t *fs,int fileHandle)
{

#ifdef _DEBUG
	printf(" - Start close file. File Handle : %d\n",fileHandle);
#endif
	fs->fileTable[fileHandle].inUse 		= 0;
	fs->fileTable[fileHandle].fd   			= 0;
	fs->fileTable[fileHandle].inode 		= 0;
	fs->fileTable[fileHandle].fileOffset   	= 0;
	memset(fs->fileTable[fileHandle].filename,'\0',MAX_FILE_NAME);

#ifdef _DEBUG
	printf(" - End close file.\n");
#endif
	return(0);
}

//	BLOCK OF Write/READ
//=============================================================================
/*
 *
 */
int fsWriteFile(fs_t *fs,int fd,const char *buffer,const int size)
{

	int InodeID 	= 	fs->fileTable[fd].inode;
	int need_b 		=	0;
	int writeOffset	=	0;
	int tempSize	=	0;
	int coun		=	0;
	int sizeCounter	=	size;
	char address[BLOCK_ADSRESS_SIZE];
	char tempBuf[BLOCK_SIZE+1];


	while(sizeCounter>0)
	{
		memset(tempBuf,'+',BLOCK_SIZE);
		need_b 			=	fs->inodeList[InodeID].fileSize/BLOCK_SIZE;
		writeOffset		=	fs->inodeList[InodeID].fileSize%BLOCK_SIZE;
		tempSize 		= 	BLOCK_SIZE - writeOffset;

		if(sizeCounter <  BLOCK_SIZE)
		{
			tempSize= sizeCounter;
		}
		else
		{
			tempSize = BLOCK_SIZE;
		}

		if(writeOffset > 0 && tempSize >=BLOCK_SIZE)
		{
			tempSize 		= 	BLOCK_SIZE - writeOffset;
		}


		for(coun=0;coun<tempSize;coun++)
		{
			tempBuf[coun] = buffer[size-sizeCounter+coun];

		}

		//if(fd)
		//	printf("\n # Temp SIZE: %d  #Offset %d  #Need b %d\n",tempSize,writeOffset,need_b);

		if(need_b < DIRECT_ENTRIES)
		{
			if(writeOffset == 0)
				fs->inodeList[InodeID].directBlocks[need_b] = AllocateBlock(fs);

			lseek(fs->fd,DATA_START+
					fs->inodeList[InodeID].directBlocks[need_b]*BLOCK_SIZE+writeOffset,
					SEEK_SET);
			write(fs->fd,tempBuf,tempSize);

			fs->inodeList[InodeID].fileSize += tempSize;
		//	if(fd)
		//		printf ("1 Writed to file %d - %s - FIle size is %d \n",tempSize,tempBuf,fs->inodeList[InodeID].fileSize);

		}
		else if(need_b >= DIRECT_ENTRIES && need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)
		{
			/*
			 * 	Here is single block writing
			 */

			int newBID_sing = 0;
			//	if the block for single enties wasnt allocated, allocate him
			if(need_b == DIRECT_ENTRIES && writeOffset == 0)
				fs->inodeList[InodeID].singleIndirectBlocks[0] = AllocateBlock(fs);

			if(writeOffset == 0)
			{


				newBID_sing = AllocateBlock(fs);
				intToChar(address,newBID_sing);

				//	Lseek for write addres
				lseek(fs->fd,DATA_START+
						fs->inodeList[InodeID].singleIndirectBlocks[0]*BLOCK_SIZE +
						(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
						SEEK_SET);

				write(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	write adress
			}
			else
			{
				lseek(fs->fd,DATA_START+
						fs->inodeList[InodeID].singleIndirectBlocks[0]*BLOCK_SIZE +
						(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
						SEEK_SET);

				read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	write adress
				forCharsToInt(address,&newBID_sing);

			}

			//	Lseek for write data
			lseek(fs->fd,DATA_START+ newBID_sing*BLOCK_SIZE + writeOffset, SEEK_SET);
			write(fs->fd,tempBuf,tempSize);					//	Write data

			fs->inodeList[InodeID].fileSize += tempSize;
		//	if(fd)
		//		printf ("2 Writed to file(tempSize)[%d] -String:[%s] - FIle size is [%d] \n",tempSize,tempBuf,fs->inodeList[InodeID].fileSize);
		}
		//					6												23
		else if(need_b>=DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS  && need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS+DOUBLE_INDIRECT_BLOCKS)
		{

			/*
			 * 	Here is double block writing
			 */
			//	Get id of block on second level
		//	if(fd)
			//	printf("\n Work with Double\n");
			int SecendLevelID = (need_b - (DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS) )/BLOCK_ADSRESS_SIZE ;
			int SecendLevelNewIDBlock = 0;	//	if need
			//printf("Need %d - Second level block %d \n",DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS ,SecendLevelID );
			//	if It is starting fill double block allocate first level block
			if(need_b == DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS && writeOffset == 0)
			{
				fs->inodeList[InodeID].doubleIndirectBlocks[0] = AllocateBlock(fs);
				//printf(" ### Created block 1 - ");
			}

			//	if need new block on second level - allocate him
			if( (need_b - (DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS))%BLOCK_ADSRESS_SIZE ==0 && writeOffset == 0)
			{
				//printf(" ### Created block 2- \n");
				SecendLevelNewIDBlock = AllocateBlock(fs);

				intToChar(address,SecendLevelNewIDBlock);
				//	Lseek for write addres
				lseek(fs->fd,DATA_START+
						fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
						SecendLevelID*BLOCK_ADSRESS_SIZE,
						SEEK_SET);
				write(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	write adress

				//SecendLevelID = SecendLevelNewIDBlock;

			}

			//	Read adress from first level
			lseek(fs->fd,DATA_START+
					fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
					SecendLevelID*BLOCK_ADSRESS_SIZE,
					SEEK_SET);

			//printf("1  Address %s Level ID- %d|||", address,SecendLevelID);
			int secondLVLentry = 0;

			read(fs->fd,address,BLOCK_ADSRESS_SIZE);

			forCharsToInt(address,&secondLVLentry);		//	Get address of second level block

			//printf("2 Address %s Level ID- %d|||", address,secondLVLentry);
			int offset_in2_lvl = (need_b - (DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS))%BLOCK_ADSRESS_SIZE ;

			//	Allocating data block - Third levlel
			int newBlcokID = 0;
			if(writeOffset == 0)
			{
				newBlcokID = AllocateBlock(fs);

				intToChar(address,newBlcokID);

				lseek(fs->fd,DATA_START+
					secondLVLentry*BLOCK_SIZE +
					offset_in2_lvl*BLOCK_ADSRESS_SIZE,
					SEEK_SET);
				write(fs->fd,address,BLOCK_ADSRESS_SIZE);
			}
			else
			{
				lseek(fs->fd,DATA_START+
					secondLVLentry*BLOCK_SIZE +
					offset_in2_lvl*BLOCK_ADSRESS_SIZE,
					SEEK_SET);
				read(fs->fd,address,BLOCK_ADSRESS_SIZE);
				forCharsToInt(address,&newBlcokID);
			}
			//printf("3 Address %s Level ID- %d in assata %d | New block adress %d|||", address,newBlcokID,offset_in2_lvl,newBlcokID);

			lseek(fs->fd,DATA_START+
					newBlcokID*BLOCK_SIZE + writeOffset ,
					SEEK_SET);

			write(fs->fd,tempBuf,tempSize);
			fs->inodeList[InodeID].fileSize += tempSize;
			//if(fd)
			//	printf ("3 Writed to file(tempSize)[%d] -String:[%s] - FIle size is [%d] \n",tempSize,tempBuf,fs->inodeList[InodeID].fileSize);


		}
		else
		{

			printf("You are here need_b %d\n",need_b);
		}

		sizeCounter -=tempSize;
	}

	return(0);
}


//=============================================================================
void fsPrintRootDir(fs_t *fs)
{

	printf("The directory is <> and contain:\n");

	char fileData[MAX_FILE_SIZE];
	char buffer[BLOCK_SIZE];
	int tempSize = 0;;
	//int counter = fs->inodeList[ROOT_DIRECTORY_HANDLE].fileSize;
	fsReadFileAll(fs,ROOT_DIRECTORY_HANDLE,fileData,&tempSize);

	int coun =0;
	int fileCounter = 0;
	struct DirEntry tempDirEntry;
	while(tempSize>0)
	{
		for(coun = 0; coun < BLOCK_SIZE;coun++)
		{
			buffer[coun] = fileData[fileCounter*BLOCK_SIZE+coun];
		}
		fileCounter++;
		memcpy(&tempDirEntry,buffer,BLOCK_SIZE);
		printf("%s \t Inode: %d\n",tempDirEntry.filename,tempDirEntry.inode);
		 //res = fsReadFile(fs,ROOT_DIRECTORY_HANDLE,buffer,&tempSize);
		 tempSize-=BLOCK_SIZE;
	}

	printf(" %d files\n",fileCounter);

	printf("End .. \n");
}

//=============================================================================
int fsReadFileAll(fs_t *fs,int fd,char *buffer,int *readSize)
{
	char tempBuffer[BLOCK_SIZE];
	int coun 		= 	0;
	int readed 		= 	0;
	*readSize 		= 	0;

	while(1)
	{
		//*readSize
		readed = fsReadFileBlock(fs,fd,tempBuffer);
		fs->fileTable[fd].fileOffset += readed;

		*readSize +=readed;
		if(readed == 0)
			break;

		for(coun = 0 ; coun < readed;coun++)
			buffer[*readSize - BLOCK_SIZE+coun] = tempBuffer[coun];
	}

	return(0);
}

//=============================================================================
/*
 * 		Function wich read from file into buffer
 * 	Getting file description , size of bytes need to read, pointer to data
 * 	structure.
 * 		Return in buffer pointer string readed, and returned value it is
 * 	size of readed bytes
 */
int fsReadFile(fs_t *fs,int fd,char *buffer,int readSize)
{
	char tempBuffer[BLOCK_SIZE];			//	BLocks buffer
	int coun = 0;							//	temp variable
	int readed = 0;							//	readed on each block read
	int readedAll = 0;						//	Size of readed in all
	int offsetNeed = 0;						//	USed for copy string


	//if(sizeof(buffer) > readSize)
	//	return(-1);
	//else

	memset(buffer,"-",sizeof(buffer));		//	inuse string format

	while(readedAll<=readSize)
	{

		readed = fsReadFileBlock(fs,fd,tempBuffer);	//	Read block
		readedAll +=readed;							//	Update readed size

		//	Check and repair offset in returned string
		if(readedAll > readSize)
			offsetNeed =BLOCK_SIZE -(readedAll - readSize) ;//	smalloffset
		else
			offsetNeed = readed;			//	simple offset

		fs->fileTable[fd].fileOffset += offsetNeed;	//	Update file offset

		//	For each char in returned tmp-buffer copy him to return buffer
		for(coun = 0 ; coun < offsetNeed;coun++)
		{
			buffer[readedAll -readed+coun] = tempBuffer[coun];

			//	If get some backslash zero don`t need put hem into text
			//	be returned becouse on end of this function we put one one
			//	the end of all global string wich be returned
			if(tempBuffer[coun] == 0)
			{
				readedAll--;		//	decrease next place of next char
				break;				//	break form for
			}

		}
//		if(readedAll >= readSize)
//		{
//			readedAll == readSize;
//			break;

//		}
	}

	buffer[readSize] = '\0';				//	but backslashzero

	return(readedAll);						//	return readed bytes
}
//=============================================================================
/*
 * 		Function for reading only one block each call
 * 	Function geting pointer to data structure wich used in our program,
 * 	File discriptor of file wich we wont to read, and buffer.
 * 		Return: funvtion return in buffer pointer the information readed
 * 	from block, and also return the size wich was readed, usualy it
 * 	is BLOCK_SIZE but if not success to read- it is happen where trying
 * 	to read more then file have so return 0 or on error -1
 */
int fsReadFileBlock(fs_t *fs,int fd,char *buffer)
{

	int InodeID 	= 	fs->fileTable[fd].inode;	//	Inode of block
	int need_b 		=	fs->fileTable[fd].fileOffset/BLOCK_SIZE;//Block need
	char address[BLOCK_ADSRESS_SIZE];				//	temp for address
	int adrINT 		= 	0;							//	variable see next

	//	Check if we over the file size trying to read
	if(fs->fileTable[fd].fileOffset >= fs->inodeList[InodeID].fileSize)
		return(0);									//	return readed


	if(need_b < DIRECT_ENTRIES)
	{
		/* Here is direct reading from block */
		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].directBlocks[need_b]*BLOCK_SIZE,
				SEEK_SET);

		read(fs->fd,buffer,BLOCK_SIZE);				//	read data
		return(BLOCK_SIZE);							//	retunr readed
	}
	else if(need_b >= DIRECT_ENTRIES
			&& need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)
	{
		/* 	Here is single block reading*/
		//	Lseek for write addres
		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].singleIndirectBlocks[0]*BLOCK_SIZE +
				(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
				SEEK_SET);

		read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read adress

		//	Lseek for write data
		forCharsToInt(address,&adrINT);				//	convert address to int
		lseek(fs->fd,DATA_START+ adrINT*BLOCK_SIZE, SEEK_SET);
		read(fs->fd,buffer,BLOCK_SIZE);				//	read data

		return(BLOCK_SIZE);							//	return readed
	}
	else if(need_b>=DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS
	&& need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS+DOUBLE_INDIRECT_BLOCKS)
	{
		/* 	Here is double block reading*/
		//	Get id of block on second level
		int SecendLevelID = (need_b - (DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS))
														/BLOCK_ADSRESS_SIZE ;
		int secondLVLentry = 0;			//	block on second level
		int offset_in2_lvl = 0;			//	offset in second level block

		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
										SecendLevelID*BLOCK_ADSRESS_SIZE,
																SEEK_SET);

		read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read address
		forCharsToInt(address,&secondLVLentry);		//	convert address

		//	calculate offset in side of first level block
		offset_in2_lvl = (need_b - (DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS))
														%BLOCK_ADSRESS_SIZE ;
		//	do lseek to right postition
		lseek(fs->fd,DATA_START+ secondLVLentry*BLOCK_SIZE +
								offset_in2_lvl*BLOCK_ADSRESS_SIZE,SEEK_SET);
		read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read sdress
		forCharsToInt(address,&adrINT);				//	convert address

		lseek(fs->fd,DATA_START+adrINT*BLOCK_SIZE ,	SEEK_SET);
		read(fs->fd,buffer,BLOCK_SIZE);				//	read DATA

		return(BLOCK_SIZE);							//	return readed
	}

	return(-1);										//	else
}


#endif
//=============================================================================
//=============================================================================
//=============================================================================
