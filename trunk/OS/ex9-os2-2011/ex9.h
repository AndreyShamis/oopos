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



int fsReadFile(fs_t *fs,int fd,char *buffer,int *readSize);
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
	fs->fileTable[fileHandle].inUse = 0;
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
#ifdef _DEBUG_WRITE
	printf(" - Start write to file - %s.\n" , buffer);
#endif


	//int newBID = findNotUsedBitMap(fs);
	int InodeID = fs->fileTable[fd].inode;
	int need_b =fs->inodeList[InodeID].fileSize/BLOCK_SIZE;
	char address[BLOCK_ADSRESS_SIZE];

	if(need_b < DIRECT_ENTRIES)
	{
		// - BLOCK_SIZE
		fs->inodeList[InodeID].directBlocks[need_b] = AllocateBlock(fs);
		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].directBlocks[need_b]*BLOCK_SIZE,
				SEEK_SET);
		write(fs->fd,buffer,size);



		fs->inodeList[InodeID].fileSize += size;
		printf ("Writed to file %d - FIle size is %d \n",size,fs->inodeList[InodeID].fileSize);

	}
	else if(need_b >= DIRECT_ENTRIES && need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)
	{
		/*
		 * 	Here is single block writing
		 */

		//	if the block for single enties wasnt allocated, allocate him
		if(need_b == DIRECT_ENTRIES)			//	== 3
			fs->inodeList[InodeID].singleIndirectBlocks[0] = AllocateBlock(fs);


		int newBID_sing = AllocateBlock(fs);
		intToChar(address,newBID_sing);

		//	Lseek for write addres
		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].singleIndirectBlocks[0]*BLOCK_SIZE +
				(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
				SEEK_SET);

		write(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	write adress

		//	Lseek for write data
		lseek(fs->fd,DATA_START+ newBID_sing*BLOCK_SIZE, SEEK_SET);
		write(fs->fd,buffer,size);					//	Write data

		fs->inodeList[InodeID].fileSize += size;
		printf ("Writed to file %d - FIle size is %d \n",size,fs->inodeList[InodeID].fileSize);
	}
	//					6												23
	else if(need_b>=DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS && need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS+DOUBLE_INDIRECT_BLOCKS)
	{
		/*
		 * 	Here is double block writing
		 */
		//	Get id of block on second level
		int SecendLevelID = (need_b - DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)/BLOCK_ADSRESS_SIZE ;
		int SecendLevelNewIDBlock = 0;	//	if need

		//	if It is starting fill double block allocate first level block
		if(need_b == DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)			//	== 6=
			fs->inodeList[InodeID].doubleIndirectBlocks[0] = AllocateBlock(fs);

		//	if need new block on second level - allocate him
		if( (need_b - DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)%BLOCK_ADSRESS_SIZE ==0 )
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

		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
				SecendLevelID*BLOCK_ADSRESS_SIZE,
				SEEK_SET);
		int secondLVLentry = 0;
		read(fs->fd,address,BLOCK_ADSRESS_SIZE);
		forCharsToInt(address,&secondLVLentry);

		int offset_in2_lvl = (need_b - DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)%BLOCK_ADSRESS_SIZE ;

		int newBlcokID = AllocateBlock(fs);
		forCharsToInt(address,&newBlcokID);
		lseek(fs->fd,DATA_START+
				secondLVLentry*BLOCK_SIZE +
				offset_in2_lvl*BLOCK_ADSRESS_SIZE,
				SEEK_SET);
		write(fs->fd,address,BLOCK_ADSRESS_SIZE);



		lseek(fs->fd,DATA_START+
				newBlcokID*BLOCK_SIZE ,
				SEEK_SET);


		write(fs->fd,buffer,size);
		fs->inodeList[InodeID].fileSize += size;
		printf ("Writed to file %d - FIle size is %d \n",size,fs->inodeList[InodeID].fileSize);

	}


#ifdef _DEBUG_WRITE
	printf(" - End write to file.\n");
#endif
	return(0);
}


//=============================================================================
void fsPrintRootDir(fs_t *fs)
{

	printf("The directory is <> and contain:\n");
	char buffer[BLOCK_SIZE];
	//int counter = fs->inodeList[ROOT_DIRECTORY_HANDLE].fileSize;
	int res = fsReadFile(fs,ROOT_DIRECTORY_HANDLE,buffer,BLOCK_SIZE);
	struct DirEntry tempDirEntry;
	while(res>0)
	{

		memcpy(&tempDirEntry,buffer,BLOCK_SIZE);
		printf("File(): %s \t Inode: %d\n",tempDirEntry.filename,tempDirEntry.inode);
		 res = fsReadFile(fs,ROOT_DIRECTORY_HANDLE,buffer,BLOCK_SIZE);
	}
//	int counter = fs->inodeList[ROOT_DIRECTORY_HANDLE].fileSize;
//
//	int single_coun = 0;
//	int b_id = 0;
//	char buffer[BLOCK_SIZE];
//	char address[BLOCK_ADSRESS_SIZE];
//	struct DirEntry tempDirEntry;
//
//	printf("Size of ROOT directory is: %d\n",counter);
//	while(counter>0)
//	{
//		printf("Counter : %d - ",counter);
//		if(b_id <3)
//		{
//			lseek(fs->fd,DATA_START +BLOCK_SIZE*fs->inodeList[ROOT_DIRECTORY_HANDLE].directBlocks[b_id], SEEK_SET);
//
//			read(fs->fd,buffer,BLOCK_SIZE);
//
//			memcpy(&tempDirEntry,buffer,BLOCK_SIZE);
//
//			printf("File(Direct): %s \t Inode: %d\n",tempDirEntry.filename,tempDirEntry.inode);
//			b_id++;
//
//
//		}
//
//		else if(b_id < 7 && b_id>2)
//		{
//			lseek(fs->fd,DATA_START +BLOCK_SIZE*fs->inodeList[ROOT_DIRECTORY_HANDLE].singleIndirectBlocks[0]+ single_coun*BLOCK_ADSRESS_SIZE, SEEK_SET);
//
//			read(fs->fd,address,BLOCK_ADSRESS_SIZE);
//
//			int newAddress = 0;
//			forCharsToInt(address, &newAddress);
//
//			lseek(fs->fd,DATA_START +newAddress*BLOCK_SIZE, SEEK_SET);
//
//			read(fs->fd,buffer,BLOCK_SIZE);
//			memcpy(&tempDirEntry,buffer,BLOCK_SIZE);
//
//			printf("File(Single): %s \t Inode: %d\n",tempDirEntry.filename,tempDirEntry.inode);
//			single_coun++;
//			b_id++;
//		}
//		counter-=BLOCK_SIZE;
//	}

	printf("End .. \n");
}

//=============================================================================
int fsReadFile(fs_t *fs,int fd,char *buffer,int *readSize)
{

#ifdef _DEBUG
	printf(" - Start read from file.\n");
#endif
	int InodeID = fs->fileTable[fd].inode;

	if(fs->fileTable[fd].fileOffset >= fs->inodeList[InodeID].fileSize)
	{
		//#ifdef _DEBUG
		//	printf(" - '''''''''''Offset big''''''''''''''.\n");
		//#endif
		return(0);
	}
	//int newBID = findNotUsedBitMap(fs);

	//int need_b =fs->inodeList[InodeID].fileSize/BLOCK_SIZE;
	int need_b =fs->fileTable[fd].fileOffset/BLOCK_SIZE;
	char address[BLOCK_ADSRESS_SIZE];
	int adrINT = 0;
	if(need_b < DIRECT_ENTRIES)
	{
		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].directBlocks[need_b]*BLOCK_SIZE,
				SEEK_SET);

		read(fs->fd,buffer,BLOCK_SIZE);
		fs->fileTable[fd].fileOffset += BLOCK_SIZE;
		return(strlen(buffer));

	}
	else if(need_b >= DIRECT_ENTRIES && need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)
	{
		/*
		 * 	Here is single block reading
		 */
		//	Lseek for write addres
		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].singleIndirectBlocks[0]*BLOCK_SIZE +
				(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
				SEEK_SET);

		read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	write adress

		//	Lseek for write data

		forCharsToInt(address,&adrINT);
		lseek(fs->fd,DATA_START+ adrINT*BLOCK_SIZE, SEEK_SET);
		read(fs->fd,buffer,BLOCK_SIZE);					//	Write data

		fs->fileTable[fd].fileOffset += BLOCK_SIZE;
		return(strlen(buffer));
	}
	//					6												23
	else if(need_b>=DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS && need_b < DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS+DOUBLE_INDIRECT_BLOCKS)
	{
		/*
		 * 	Here is double block writing
		 */
		//	Get id of block on second level
		int SecendLevelID = (need_b - DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)/BLOCK_ADSRESS_SIZE ;
		int SecendLevelNewIDBlock = 0;	//	if need

		lseek(fs->fd,DATA_START+
				fs->inodeList[InodeID].doubleIndirectBlocks[0]*BLOCK_SIZE +
				SecendLevelID*BLOCK_ADSRESS_SIZE,
				SEEK_SET);
		int secondLVLentry = 0;
		read(fs->fd,address,BLOCK_ADSRESS_SIZE);
		forCharsToInt(address,&secondLVLentry);

		int offset_in2_lvl = (need_b - DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)%BLOCK_ADSRESS_SIZE ;

		//int newBlcokID = AllocateBlock(fs);

		lseek(fs->fd,DATA_START+
				secondLVLentry*BLOCK_SIZE +
				offset_in2_lvl*BLOCK_ADSRESS_SIZE,
				SEEK_SET);
		read(fs->fd,address,BLOCK_ADSRESS_SIZE);


		forCharsToInt(address,&adrINT);

		lseek(fs->fd,DATA_START+
				adrINT*BLOCK_SIZE ,
				SEEK_SET);


		read(fs->fd,buffer,BLOCK_SIZE);
		fs->fileTable[fd].fileOffset += BLOCK_SIZE;
		return(strlen(buffer));
		//printf ("Writed to file %d - FIle size is %d \n",size,fs->inodeList[InodeID].fileSize);

	}

#ifdef _DEBUG
	printf(" - End read from file.\n");
#endif
	return(0);
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
void PrintStatistic(fs_t *fs);

#endif
//=============================================================================
//=============================================================================
//=============================================================================
