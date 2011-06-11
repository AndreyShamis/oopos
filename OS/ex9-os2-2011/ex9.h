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

#include "defines.inc.h"		//	inlude globals- fefines
#include "errors.inc.h"			//	include errors page
#include "structures.inc.h"		//	include structures

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
 * 	Print information such:
 * 	-	Status of bitmap usage
 * 	-	Files in directory(we have only one)
 * 	-	Size of each file
 * 	-	And list of block for each file*/
void PrintStatistic(fs_t *fs);
//=============================================================================
/*
 * 		Function which serach in struct which fileTable not in use.
 * 	Geting pointer to main data base structure.
 * Return n>0 if finded somthing ot -1 if not*/
int findNotUsedFD(fs_t *fs);
//=============================================================================
/*
 *		Function for create file in our file system
 *	Function get pointer main data structure and the name of new file
 *	Return file desctiptor of new file or -1 if not success create file*/
int fsCreateFile(fs_t *fs,char *fileName);
//=============================================================================
/*
 *		Function for open file
 *		Function Get pointer to main structure of our program and file name
 *		wich need open
 *		Return file descriptor if success open file or -1 on fail*/
int fsOpenFile(fs_t *fs,char *fileName);
//=============================================================================
/*
 *		Function wich close open file.
 *		Function get pointer to our main data structure and file handle
 *		Function return 0 on success or -1 on fail */
int fsCloseFile(fs_t *fs,int fileHandle);
//=============================================================================
/*
 *		Function wich write data into file
 *		Function get pointer to main data structure,file descriptor of file
 *	in wich we wont to write data, buuffer contein the data wich we want to
 *	in write and size of data wich be writed
 *		Function return size of writed data  or -1 on fail */
int fsWriteFile(fs_t *fs,int fd,const char *buffer,const int size);
//=============================================================================
/*
 * 		Function wich reading all data in file
 * 	Function get pointer to main data structure , file descriptor of file
 * wich we wont to read, also buffer for data (must be in size of file), and
 * in last we get pointer
 * 	Function return 0 on success or -1 on fail */
int fsReadFileAll(fs_t *fs,int fd,char *buffer,int *readSize);
//=============================================================================
/*
 * 		Function wich allocate block and set need variables to know if block
 * allocated and where and how.
 * 		Function get pointer to main data structure
 * 		Function return block ID if success or -1 if fail*/
int AllocateBlock(fs_t *fs);
//=============================================================================
/*
 *		Function wich provide onmount operation
 *		Function get poiunter to main data structure*/
int fsUnMount(fs_t *fs);
//=============================================================================
/*
 * 		Function wich print all direcotory entry - all files
 * 		Function get pointer to main data structure */
void fsPrintRootDir(fs_t *fs);
//=============================================================================
/*
 *		Function wich load all inodes from file system from inode sector
 *		Function get pointer to main data structure */
void PrepareAllInodesOnMount(fs_t *fs);
//=============================================================================
/*
 *		Function for create new file system file
 *		Function get New system file name.
 *		Function return 0 on success*/
int fsCreateFileSystem(char *filename);
//=============================================================================
/*
 *		Function for saving bit maps(coverting to int) and saving indes
 *		without converting
 *		Function get pointer to main data structure */
void SaveToFS_BitMap_INODES(fs_t *fs);
//=============================================================================
/*
 *		Function for format file system
 *		Function get pinter to main dta structure
 *		Function return 0 on seccess or -1 on fail*/
int fsFormat(fs_t *fs);


//=============================================================================
void privateWriteLog(fs_t *fs,const int errorID);


//=============================================================================
/*
 *		Function for format file system
 *		Function get pinter to main dta structure
 *		Function return 0 on seccess or -1 on fail
 */
int fsFormat(fs_t *fs)
{
	int coun = 0;						//	temp variable

	for(coun=0;coun<NR_BLOCKS;coun++)	//	preapre bitmap
		fs->Bitmap[coun] = 0;

	//	Prepare Inodes
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

	//	Prepare root direcotory information
	fs->pRootInode = &fs->inodeList[ROOT_DIRECTORY_HANDLE];
	fs->pRootInode->inUse = 1;
	fs->fileTable[ROOT_DIRECTORY_HANDLE].inode 	= 	ROOT_DIRECTORY_HANDLE;
	fs->fileTable[ROOT_DIRECTORY_HANDLE].inUse 	= 	1;
	fs->fileTable[ROOT_DIRECTORY_HANDLE].fd		=	ROOT_DIRECTORY_HANDLE;
	fs->fileTable[ROOT_DIRECTORY_HANDLE].fileOffset =0 ;


	fs->fsInitialized = 1;				//	set initilized
	SaveToFS_BitMap_INODES(fs);			//	Save Main structure to file

	lseek(fs->fd,DATA_START,SEEK_SET);	//	lseek into data sector

	char tmpBuffer[BLOCK_SIZE];			//	Create temp buffer

	memset(tmpBuffer,'-',BLOCK_SIZE);	//	write some information to tmpBLock

	int res= 0;
	for(coun = 0 ; coun < NR_BLOCKS;coun++)
	{

		res= write(fs->fd,tmpBuffer,BLOCK_SIZE);

		if(res < 0)
		{
			printf("Cant write. Iteration num: %d\n",coun);
		}

	}
	//PrepareAllInodesOnMount(fs);

	return(0);

}
//=============================================================================
/*
 *		Function wich load all inodes from file system from inode sector
 *		Function get pointer to main data structure
 */
void PrepareAllInodesOnMount(fs_t *fs)
{
	int coun = 0;


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
//=============================================================================
/*
 *		Function for saving bit maps(coverting to int) and saving indes
 *		without converting
 *		Function get pointer to main data structure
 */
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
	ret->lastErrEntry =	0;

	for(coun=0;coun<MAX_ERRORS;coun++)
	{
		ret->lastErrors[coun] = 0;
	}

	return(ret);
}

void printLog(fs_t *fs)
{
	int coun = 0;
	for(coun=0;coun<MAX_ERRORS;coun++)
	{
		if(fs->lastErrors[coun])
			printf("Error %d \n",fs->lastErrors[coun]);
	}
}
//=============================================================================
void privateWriteLog(fs_t *fs,const int errorID)
{
	if(fs->lastErrEntry == MAX_ERRORS)
	{

	}
	fs->lastErrors[fs->lastErrEntry] = errorID;
	fs->lastErrEntry++;

}
//=============================================================================
/*
 *		Function wich provide onmount operation
 *		Function get poiunter to main data structure
 */
int fsUnMount(fs_t *fs)
{
	SaveToFS_BitMap_INODES(fs);

	if(munmap(fs->source, fs->filesize) == -1)
		perror("Error un-mmapping the file\n");

	close(fs->fd);
	free(fs);
	return(0);
}
//=============================================================================
/*
 * 		Function wich allocate block and set need variables to know if block
 * allocated and where and how.
 * 		Function get pointer to main data structure
 * 		Function return block ID if success or -1 if fail
 */
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
 *		Function for create file in our file system
 *	Function get pointer main data structure and the name of new file
 *	Return file desctiptor of new file or -1 if not success create file
 */
int fsCreateFile(fs_t *fs,char *fileName)
{
	int coun 				= 0;			//	temp variable
	int ret_FD 				= 0;			//	FD of new file be created
	char newFileName[MAX_FILE_NAME];		//	temp variable
	struct DirEntry newFile;				//	Struct for new file


	if(sizeof(fileName) >= MAX_FILE_NAME)
		return(-1);

	coun = fsOpenFile(fs,fileName);

	//	Here we are checking if file with this name exist, if yes -
	//	can open file with name so close the file and exit from this function
	//	with error code -1
	if(coun != -1)
	{
		fsCloseFile(fs,coun);				//	Close open file
		privateWriteLog(fs,ERR_FILE_EXIST);
		return(-1);							//	return error code
	}

	memset(newFileName,'+',MAX_FILE_NAME);	//
	strcpy(newFileName,fileName);			//	DONT CHANGE TO MEMCPY.
	//	This function put \0 on right space

	if(fs->fsInitialized)
	{
		int newIndoeID = findNotUsedIndoe(fs);	//	get free inode

		//	Check if indoe was returned is good
		if(newIndoeID>=0)
		{
				ret_FD = findNotUsedFD(fs);
				//	Set name
				memcpy(&newFile.filename,newFileName,MAX_FILE_NAME);
				newFile.inode = newIndoeID;		//	set Inode id

				char buffer[MAX_FILE_NAME + BLOCK_ADSRESS_SIZE];

				//	Preparing write data to file (Direcroty)
				memcpy(buffer,&newFile,MAX_FILE_NAME + BLOCK_ADSRESS_SIZE);
				fsWriteFile(fs,ROOT_DIRECTORY_HANDLE,buffer,sizeof(buffer));

			fs->inodeList[newIndoeID].inUse = 1;
			fs->fileTable[ret_FD].inUse = 1;
			fs->fileTable[ret_FD].fd = ret_FD;
			fs->fileTable[ret_FD].inode = newIndoeID;


		}
		else
		{

			printf("TODO:-All Indoes used. Can`t create file!\n");
			return(newIndoeID);
		}

		//printf("TODO:+Success create file\n");

		return(ret_FD);
	}
	else
	{
		privateWriteLog(fs,ERR_NEED_FORMAT);
		printf("TODO:-Canot create file %s, you need format file system.\n",
				fileName);
		return(-1);

	}
}
//=============================================================================
/*
 *
 */
int findFileNode(fs_t *fs,char *fileName)
{
	char fileData[MAX_FILE_SIZE];
	char buffer[BLOCK_SIZE];
	int tempSize = 0;;

	fsReadFileAll(fs,ROOT_DIRECTORY_HANDLE,fileData,&tempSize);

	int coun =0;
	int fileCounter = 0;
	struct DirEntry tempDirEntry;

	while(tempSize>0)
	{
		//printf("LA LA %d\n",tempSize);
		for(coun = 0; coun < BLOCK_SIZE;coun++)
		{
			buffer[coun] = fileData[fileCounter*BLOCK_SIZE+coun];
		}
		fileCounter++;
		memcpy(&tempDirEntry,buffer,BLOCK_SIZE);

		if(strcmp(tempDirEntry.filename,fileName) == 0)
		{
			return(tempDirEntry.inode);
		}

		 tempSize-=BLOCK_SIZE;
	}
	//printf("END LA\n");
	return(-1);
}
//=============================================================================
/*
 *		Function for open file
 *		Function Get pointer to main structure of our program and file name
 *		wich need open
 *		Return file descriptor if success open file or -1 on fail
 */
int fsOpenFile(fs_t *fs,char *fileName)
{
	int Inode 	= findFileNode(fs,fileName);	//	Find Inode by name
	int FD		= findNotUsedFD(fs);			//	Find free file table

	//	Check if founded file by name and free file table
	//printf("Inode found %d FD found %d\n",Inode,FD);
	if(Inode >0 && FD >0 )
	{
		fs->fileTable[FD].inUse 		= 	1;		//	set used
		fs->fileTable[FD].inode 		= 	Inode;	//	set id of inode
		strcpy(fs->fileTable[FD].filename,fileName);//	copy file name
		fs->fileTable[FD].fd			=	FD;		//	set fd
		fs->fileTable[FD].fileOffset	=	0;		//	reset offset

		return(FD);									//	return file descriptor
	}

	return(-1);									//	on fail return error code
}
//=============================================================================
/*
 *		Function wich close open file.
 *		Function get pointer to our main data structure and file handle
 *		Function return 0 on success or -1 on fail
 */
int fsCloseFile(fs_t *fs,int fileHandle)
{
	//	First check if file realy open
	if(fs->fileTable[fileHandle].inUse)
	{
		fs->fileTable[fileHandle].inUse 		= 0;
		fs->fileTable[fileHandle].fd   			= 0;
		fs->fileTable[fileHandle].inode 		= 0;
		fs->fileTable[fileHandle].fileOffset   	= 0;
		memset(fs->fileTable[fileHandle].filename,'\0',MAX_FILE_NAME);

		return(0);
	}
	else
	{
		privateWriteLog(fs,ERR_CLOSE_CLOSED_F);
	}
	return(-1);
}

//	BLOCK OF Write/READ
//=============================================================================
/*
 *		Function wich write data into file
 *		Function get pointer to main data structure,file descriptor of file
 *	in wich we wont to write data, buuffer contein the data wich we want to
 *	in write and size of data wich be writed
 *		Function return size of writed data  or -1 on fail
 */
int fsWriteFile(fs_t *fs,int fd,const char *buffer,const int size)
{

	int InodeID 	= 	fs->fileTable[fd].inode;	//	Get INODE ID
	int need_b 		=	0;//Important var wich know to wich block write data
	int writeOffset	=	0;				//	write offset
	int tempSize	=	0;				//	temp variable off size be writed
	int coun		=	0;				//	temp variable
	int sizeCounter	=	size;			//	counter of bytes need write
	char address[BLOCK_ADSRESS_SIZE];	//	temp Address variable
	char tempBuf[BLOCK_SIZE+1];			//	temp buffer variable

	//if(fd == ROOT_DIRECTORY_HANDLE && size != 16)
	//{
	//	return(-1);
	//}
	if(fd <0 || fs->fileTable[fd].inUse != 1 || fs->inodeList[InodeID].inUse !=1 )
	{
		//printf("####We are here %d %d %d\n",fs->fileTable[fd].inUse,fs->inodeList[InodeID].inUse,fd  );
		return(-1);
	}
	while(sizeCounter>0)
	{
		memset(tempBuf,'+',BLOCK_SIZE);
		need_b 			=	fs->inodeList[InodeID].fileSize/BLOCK_SIZE;
		writeOffset		=	fs->inodeList[InodeID].fileSize%BLOCK_SIZE;
		tempSize 		= 	BLOCK_SIZE - writeOffset;

		if(sizeCounter <  BLOCK_SIZE)
			tempSize= sizeCounter;
		else
			tempSize = BLOCK_SIZE;

		if(writeOffset > 0 && tempSize >=BLOCK_SIZE)
			tempSize 		= 	BLOCK_SIZE - writeOffset;


		for(coun=0;coun<tempSize;coun++)
			tempBuf[coun] = buffer[size-sizeCounter+coun];


		if(need_b < DIRECT_ENTRIES)
		{
			if(writeOffset == 0)
				fs->inodeList[InodeID].directBlocks[need_b]=AllocateBlock(fs);

			lseek(fs->fd,DATA_START+
					fs->inodeList[InodeID].directBlocks[need_b]*BLOCK_SIZE+
													writeOffset,SEEK_SET);
			write(fs->fd,tempBuf,tempSize);

			fs->inodeList[InodeID].fileSize += tempSize;

		}
		else if(need_b >= DIRECT_ENTRIES && need_b < DOUBLE_START)
		{		/* 	Here is single block writing*/

			int BlockID = 0;

			//	if the block for single enties wasnt allocated, allocate him
			if(need_b == DIRECT_ENTRIES && writeOffset == 0)
				fs->inodeList[InodeID].singleIndirectBlocks[0]=AllocateBlock(fs);

			if(writeOffset == 0)
			{
				BlockID = AllocateBlock(fs);
				intToChar(address,BlockID);

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
				forCharsToInt(address,&BlockID);

			}

			//	Lseek for write data
			lseek(fs->fd,DATA_START+ BlockID*BLOCK_SIZE + writeOffset, SEEK_SET);
			write(fs->fd,tempBuf,tempSize);					//	Write data

			fs->inodeList[InodeID].fileSize += tempSize;
		}
		else if(need_b>=DOUBLE_START && need_b < BLOCKS_PER_INODE)
		{
			/* * 	Here is double block writing*/
			//	Get id of block on second level
			int SecendLevelID =(need_b-DOUBLE_START)/BLOCK_ADSRESS_SIZE ;
			int SecendLevelNewIDBlock = 0;	//	if need

			//	if It is starting fill double block allocate first level block
			if(need_b == DOUBLE_START && writeOffset == 0)
				fs->inodeList[InodeID].doubleIndirectBlocks[0] = AllocateBlock(fs);


			//	if need new block on second level - allocate him
			if( (need_b - (DOUBLE_START))%BLOCK_ADSRESS_SIZE ==0 && writeOffset == 0)
			{
				SecendLevelNewIDBlock = AllocateBlock(fs);

				intToChar(address,SecendLevelNewIDBlock);
				//	Lseek for write addres
				lseek(fs->fd,DATA_START+
						fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
						SecendLevelID*BLOCK_ADSRESS_SIZE,
						SEEK_SET);
				write(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	write adress

			}

			//	Read adress from first level
			lseek(fs->fd,DATA_START+
					fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
					SecendLevelID*BLOCK_ADSRESS_SIZE,
					SEEK_SET);

			int secondLVLentry = 0;

			read(fs->fd,address,BLOCK_ADSRESS_SIZE);
			//	Get address of second level block
			forCharsToInt(address,&secondLVLentry);

			int offset_in2_lvl = (need_b - DOUBLE_START)%BLOCK_ADSRESS_SIZE ;

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

			lseek(fs->fd,DATA_START+
					newBlcokID*BLOCK_SIZE + writeOffset ,
					SEEK_SET);

			write(fs->fd,tempBuf,tempSize);
			fs->inodeList[InodeID].fileSize += tempSize;
		}
		else
		{
			privateWriteLog(fs,ERR_FILE_FULL);
			printf("You cannot write any more\n");
		}

		sizeCounter -=tempSize;
	}

	return(-1);
}


//=============================================================================
/*
 * 		Function wich print all direcotory entry - all files
 * 		Function get pointer to main data structure
 */
void fsPrintRootDir(fs_t *fs)
{

	printf("The directory is %s and contain:\n",ROOT_DIR_NAME);

	char fileData[MAX_FILE_SIZE];		//	Place to get all data in file
	char buffer[BLOCK_SIZE];			//	BLock data
	int tempSize 		= 	0;			//	temp variable
	int coun 			=	0;			//	temp variable
	int fileCounter 	= 	0;			//	Counter of files in directory

	struct DirEntry tempDirEntry;
	//	Set file offset be zero becouse we want to read all information
	//	in file from start file to end and my be some operation set the
	//	offset to enother place in reading. In our case function wich
	//	checking if file exist on the disk can do that
	fs->fileTable[ROOT_DIRECTORY_HANDLE].fileOffset = 0;
	//	Read all data in file-directory
	fsReadFileAll(fs,ROOT_DIRECTORY_HANDLE,fileData,&tempSize);

	while(tempSize>0)
	{
		//	Copy data(block) into temp buffer
		for(coun = 0; coun < BLOCK_SIZE;coun++)
			buffer[coun] = fileData[fileCounter*BLOCK_SIZE+coun];

		fileCounter++;					//	update file counter

		memcpy(&tempDirEntry,buffer,BLOCK_SIZE);	//	copy memory
		//	Print information to user
		printf("%s \t Inode: %d\n",tempDirEntry.filename,tempDirEntry.inode);
		 tempSize-=BLOCK_SIZE;			//	decrase size wich need to read
	}

	printf("%d files\n",fileCounter);	//	print how many files in directory

}

//=============================================================================
/*
 * 		Function wich reading all data in file
 * 	Function get pointer to main data structure , file descriptor of file
 * wich we wont to read, also buffer for data (must be in size of file), and
 * in last we get pointer
 * 	Function return 0 on success or -1 on fail
 */
int fsReadFileAll(fs_t *fs,int fd,char *buffer,int *readSize)
{
	char tempBuffer[BLOCK_SIZE];		//	temp buffer
	int coun 		= 	0;				//	temp variable
	int readed 		= 	1;				//	var of readed in each moment

	*readSize 		= 	0;				//	update returned value

	//	Start reading off all data block by block
	fs->fileTable[fd].fileOffset =0;
	while(readed)						//	TODO was while 1 and readed =1
	{
		readed = 	fsReadFileBlock(fs,fd,tempBuffer);	//	read block
		fs->fileTable[fd].fileOffset += readed;			//	update offset

		*readSize +=readed;				//	update returned variable
//		if(readed == 0)					//	check if readed something
//			break;						//	if no exit
		//	Copy readed data from tempBuffer
		for(coun = 0 ; coun < readed;coun++)
			buffer[*readSize - BLOCK_SIZE+coun] = tempBuffer[coun];
	}

	return(0);							//	return 0 on success
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
	char tempBuffer[BLOCK_SIZE+1];			//	BLocks buffer
	int coun = 0;							//	temp variable
	int readed = 0;							//	readed on each block read
	int readedAll = 0;						//	Size of readed in all
	int offsetNeed = 0;						//	USed for copy string
	int inode		=	fs->fileTable[fd].inode;

	if(fd <0 || fs->fileTable[fd].inUse != 1 || fs->inodeList[inode].inUse !=1)
	{
		//printf("####We are here %d %d %d\n",fs->fileTable[fd].inUse,fs->inodeList[InodeID].inUse,fd  );
		return(-1);
	}
	//if(sizeof(buffer) > readSize)
	//	return(-1);
	//else

	memset(buffer,0xFF,sizeof(buffer)*sizeof(char));//	inuse string format

	while(readedAll<=readSize &&
			fs->inodeList[inode].fileSize >= fs->fileTable[fd].fileOffset)
	{
		//printf("QQQQQQQQQQQQQq %d\n",readSize);
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
		//printf("AAAAAAAAAAAAAAAAAAAAAAAAASsds %d\n",readedAll);
	}

	buffer[readSize] = '\0';				//	but backslashzero

	return(readedAll);						//	return readed bytes
}
//=============================================================================
void readBlockData(fs_t *fs,char *dataBuff,const int blockID)
{
	lseek(fs->fd,DATA_START+blockID*BLOCK_SIZE,	SEEK_SET);

	read(fs->fd,dataBuff,BLOCK_SIZE);				//	read data
}
//=============================================================================

int getAddress(fs_t *fs,const int blockID,const int AdressSET)
{

	char address[BLOCK_ADSRESS_SIZE];				//	temp for address
	int returnAdr = 0;
	lseek(fs->fd,
		DATA_START+blockID*BLOCK_SIZE+AdressSET*BLOCK_ADSRESS_SIZE,	SEEK_SET);

	read(fs->fd,address,BLOCK_ADSRESS_SIZE);				//	read data
	forCharsToInt(address,&returnAdr);				//	convert address to int


	return(returnAdr);
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
	{
		if(fs->fileTable[fd].fileOffset > fs->inodeList[InodeID].fileSize)
				privateWriteLog(fs,ERR_FILE_FULL);

		return(0);									//	return readed
	}

	if(need_b < DIRECT_ENTRIES)
	{
		/* Here is direct reading from block */
	//	lseek(fs->fd,DATA_START+
	//			fs->inodeList[InodeID].directBlocks[need_b]*BLOCK_SIZE,
	//			SEEK_SET);

	//	read(fs->fd,buffer,BLOCK_SIZE);				//	read data
		readBlockData(fs,buffer,fs->inodeList[InodeID].directBlocks[need_b]);
		return(BLOCK_SIZE);							//	retunr readed
	}
	else if(need_b >= DIRECT_ENTRIES && need_b < DOUBLE_START)
	{
		/* 	Here is single block reading*/
		//	Lseek for write addres

		//lseek(fs->fd,DATA_START+
		//		fs->inodeList[InodeID].singleIndirectBlocks[0]*BLOCK_SIZE +
		//		(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
		//		SEEK_SET);

		//read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read adress

		//	Lseek for write data
		//forCharsToInt(address,&adrINT);				//	convert address to int
		adrINT = getAddress(fs,fs->inodeList[InodeID].singleIndirectBlocks[0],(need_b-DIRECT_ENTRIES));
		readBlockData(fs,buffer,adrINT);
		//lseek(fs->fd,DATA_START+ adrINT*BLOCK_SIZE, SEEK_SET);
		//read(fs->fd,buffer,BLOCK_SIZE);				//	read data

		return(BLOCK_SIZE);							//	return readed
	}
	else if(need_b>=DOUBLE_START && need_b < BLOCKS_PER_INODE)
	{
		/* 	Here is double block reading*/
		//	Get id of block on second level
		int SecendLevelID = (need_b - DOUBLE_START)	/BLOCK_ADSRESS_SIZE ;
		int secondLVLentry = 0;			//	block on second level
		int offset_in2_lvl = 0;			//	offset in second level block

		//lseek(fs->fd,DATA_START+
		//		fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
		//								SecendLevelID*BLOCK_ADSRESS_SIZE,
		//														SEEK_SET);

		//read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read address
		//forCharsToInt(address,&secondLVLentry);		//	convert address

		secondLVLentry = getAddress(fs,fs->inodeList[InodeID].doubleIndirectBlocks[0],SecendLevelID);
		//readBlockData(fs,buffer,adrINT);
		//readBlockData(fs,buffer,adrINT);

		//	calculate offset in side of first level block
		offset_in2_lvl = (need_b -DOUBLE_START)%BLOCK_ADSRESS_SIZE ;
		//	do lseek to right postition
		//lseek(fs->fd,DATA_START+ secondLVLentry*BLOCK_SIZE +
		//						offset_in2_lvl*BLOCK_ADSRESS_SIZE,SEEK_SET);
		//read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read sdress
		//forCharsToInt(address,&adrINT);				//	convert address

		adrINT = getAddress(fs,secondLVLentry,offset_in2_lvl);
		//readBlockData(fs,buffer,adrINT);
		readBlockData(fs,buffer,adrINT);
		//lseek(fs->fd,DATA_START+adrINT*BLOCK_SIZE ,	SEEK_SET);
		//read(fs->fd,buffer,BLOCK_SIZE);				//	read DATA

		return(BLOCK_SIZE);							//	return readed
	}
	printf("fsgsgdfgsdfgsfgsdfgsdfg %d\n",need_b);
	return(-1);										//	else
}

//=============================================================================
/*
 *		Function for create new file system file
 *		Function get New system file name.
 *		Function return 0 on success
 */
int fsCreateFileSystem(char *filename)
{
	int fileSize 	= 	NR_BLOCKS+NR_INODES*NODE_SIZE+NR_BLOCKS*BLOCK_SIZE;
	int fd			=	0;	//	file descriptor

	if(creat(filename,0600) == -1)
	{
		perror("Cannot create new simulation file.\n");
		exit(EXIT_FAILURE);
	}

	fd = open(FILENAME,O_RDWR | O_CREAT);

	if(fd == -1)
	{
		perror("Cannot open simulation file.\n");
		exit(EXIT_FAILURE);
	}


	lseek(fd,fileSize,SEEK_SET);
	if(write(fd,"-",1) == -1)
	{
		perror("Cannot write to simulation file.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Created simulation file[%s], of size %d\n",filename,fileSize);
	}

	return(0);
}










//=============================================================================
/*
 * 		Function for convert char(string) to int
 * 	Geting String wich need convert and pointer to int in wich be returned
 * 	the value.
 */
void forCharsToInt(char val[BLOCK_ADSRESS_SIZE],int *retValue)
{
	*retValue = atoi(val);			//	Convert string to int
}

//=============================================================================
/*
 * 		Function for convert int to char
 * 	Geting integer wich need convert and char in wich be retuned
 * converted value
 */
void intToChar(char val[BLOCK_ADSRESS_SIZE],const int valInt)
{
	int n = valInt;						//	work variable
	int coun = 0;						//	temp variable

	//	Filing the char by zeros
	for(coun = 0;coun < BLOCK_ADSRESS_SIZE ; coun++)
		val[coun] = '0';

	coun = BLOCK_ADSRESS_SIZE;							//	size of char
	//	While have devision do
    while (n!=0)
    {
    	coun--;							//	decrease counter
        val[coun]=(n%DEC_DEV) + '0';	//put the new value in spec index in
        n /= DEC_DEV;					//	char-string and devide by 10
    }
}

//=============================================================================
/*
 * 		Function which serach in struct which Inode not in use.
 * 	Geting pointer to main data base structure.
 * Return n>0 if finded somthing ot -1 if not
 */
int findNotUsedIndoe(fs_t *fs)
{
	int coun = 0;						//	temp variable

	//	For each entry to inode check if the inode
	for(coun =0;coun <NR_INODES;coun++)
		if(!fs->inodeList[coun].inUse)
			return(coun);				//	return founded

	return(-1);							//	if not found return -1

}

//=============================================================================
/*
 * 		Function which serach in struct which fileTable not in use.
 * 	Geting pointer to main data base structure.
 * Return n>0 if finded somthing ot -1 if not
 */
int findNotUsedFD(fs_t *fs)
{
	int coun = 0;						//	temp variable

	//	For each entry to inode check if the inode
	for(coun =1;coun <NR_INODES;coun++)
		if(!fs->fileTable[coun].inUse)
			return(coun);				//	return founded

	return(-1);							//	if not found return -1

}

//=============================================================================
/*		Function wich looking in main data base wich bitmap is in not use.
 * 		Get pointer to main data base.
 * 		Return n>=0 if found; -1 if not found
 */
int findNotUsedBitMap(fs_t *fs)
{
	int coun=0;							//	temp variable

	//	Trying to find free block in disk weich not used
	for(coun=0;coun<NR_BLOCKS;coun++)
		if(fs->Bitmap[coun] == 0)		//	if not used
			return(coun);				//	return index

	return(-1);							//	return negative value
}

//=============================================================================
/*
 * 		Function wich print statistic about program simulation.
 * 	Get pointer to main data base.
 *
 * 	Print information such:
 * 	-	Status of bitmap usage
 * 	-	Files in directory(we have only one)
 * 	-	Size of each file
 * 	-	And list of block for each file
 */
void PrintStatistic(fs_t *fs)
{

	#ifdef _SHOW_STATISTIC

	int coun = 0;					//	temp variable

	printf(" # - Printing table of bitmaps %d x %d = %d:\n",
			NR_BLOCKS/NR_INODES,NR_INODES,NR_BLOCKS);

	//	For each block print if the block used ot not
	for(coun=0;coun< NR_BLOCKS;coun++)
	{
		printf("%d",fs->Bitmap[coun]);

		//	Print the information in few lines for better understeind
		if((coun+1)%NR_INODES == 0)
			printf("\n");

	}
	printf("\n");

	fsPrintRootDir(fs);				//	print files in our directory


	#endif
}

#endif
//=============================================================================
//=============================================================================
//=============================================================================
