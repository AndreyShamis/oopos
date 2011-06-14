#include "ex9.h"
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

	privateWriteLog(fs,ERR_ALL_INODES_FULL);

	return(-1);							//	if not found return -1

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
		printf("%s\n",tempDirEntry.filename);
		 tempSize-=BLOCK_SIZE;			//	decrase size wich need to read
	}

	printf("%d files\n",fileCounter);	//	print how many files in directory

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

	privateWriteLog(fs,ERR_ALL_FDT_FULL);

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

	privateWriteLog(fs,ERR_ALL_BLOCKS_FULL);

	return(-1);							//	return negative value
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
 *		Function wich load all inodes from file system from inode sector
 *		Function get pointer to main data structure
 */
void PrepareAllInodesOnMount(fs_t *fs)
{
	int coun 	= 	0;			//	temp variable
	int temp	=	0;			//	also temp variable
	char buffer[NODE_SIZE];		//	buffer for data

	for(coun = 0 ; coun < NR_INODES;coun++)
	{
		//	Load all data from hard drive
		for(temp = 0;temp < NODE_SIZE;temp++)
			buffer[temp] = fs->source[NR_BLOCKS+coun*NODE_SIZE + temp];

		memcpy(&fs->inodeList[coun],buffer,NODE_SIZE);//memmove
		//	prepare also file table
		fs->fileTable[coun].inUse 		= 	0;
		fs->fileTable[coun].fileOffset 	= 	0;
		fs->fileTable[coun].fd 			= 	0;
		fs->fileTable[coun].inode 		= 	0;
	}
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
	while(readed)						//	was while 1 and readed =1
	{
		readed = 	fsReadFileBlock(fs,fd,tempBuffer);	//	read block
		fs->fileTable[fd].fileOffset += readed;			//	update offset

		*readSize +=readed;				//	update returned variable

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
	int inode		=	0;

	memset(buffer,0xFF,sizeof(buffer)*sizeof(char));//	inuse string format

	if(checkFileDescUsage(fs,fd) != -1)		//	check fd boundary
	{
		inode 	= 	fs->fileTable[fd].inode;	//	get inode ID
		if(fs->inodeList[inode].inUse != 1)	//	check if inode is good
		{
			privateWriteLog(fs,ERR_INCORECT_INODE);	//	write error
			return(-1);						//	exit
		}
	}
	else
	{
		privateWriteLog(fs,ERR_READ_CLOSED);//	write error id
		privateWriteLog(fs,ERR_ON_READ);	//	write error id
		return(-1);							//	return error
	}

	//	while have data to read and offset smaller then size
	while(readedAll<=readSize &&
			fs->inodeList[inode].fileSize >= fs->fileTable[fd].fileOffset)
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
		readBlockData(fs,buffer,fs->inodeList[InodeID].directBlocks[need_b]);

		return(BLOCK_SIZE);							//	retunr readed
	}
	else if(need_b >= DIRECT_ENTRIES && need_b < DOUBLE_START)
	{
		/* 	Here is single block reading*/
		adrINT = getAddress(fs,fs->inodeList[InodeID].singleIndirectBlocks[0],
				(need_b-DIRECT_ENTRIES));
		readBlockData(fs,buffer,adrINT);
		return(BLOCK_SIZE);							//	return readed
	}
	else if(need_b>=DOUBLE_START && need_b < BLOCKS_PER_INODE)
	{
		/* 	Here is double block reading*/
		//	Get id of block on second level
		int AddressSET = (need_b - DOUBLE_START)	/BLOCK_ADSRESS_SIZE ;

		adrINT = getAddress(fs,fs->inodeList[InodeID].doubleIndirectBlocks[0],
				AddressSET);
		//	calculate offset in side of second level block
		AddressSET = (need_b -DOUBLE_START)%BLOCK_ADSRESS_SIZE ;
		adrINT = getAddress(fs,adrINT,AddressSET);
		readBlockData(fs,buffer,adrINT);

		return(BLOCK_SIZE);							//	return readed
	}

	privateWriteLog(fs,ERR_UNKNOWN_ON_WRITE_BLOCK);	//	write error
	return(-1);										//	else
}

//=============================================================================
/*
 *		Function for saving bit maps(coverting to int) and saving indes
 *		without converting
 *		Function get pointer to main data structure
 */
void SaveToFS_BitMap_INODES(fs_t *fs)
{
	int coun	= 	0;						//	temp variable
	int tempI	=	0;						//	temp variable
	char buffer[NODE_SIZE];					//	buffer for inoders

	//	Convert and write bitmaps
	for(coun=0;coun<NR_BLOCKS;coun++)
		fs->source[coun]= fs->Bitmap[coun] + '0';

	//	get and write inodes
	for(coun = 0 ; coun < NR_INODES;coun++)
	{
		memcpy(buffer,&fs->inodeList[coun],NODE_SIZE);	//	set memory

		for(tempI = 0;tempI < NODE_SIZE;tempI++)
			fs->source[NR_BLOCKS+coun*NODE_SIZE + tempI] = buffer[tempI];

	}
}

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

	int InodeID 	= 	0;				//	 INODE ID
	int need_b 		=	0;//Important var wich know to wich block write data
	int writeOffset	=	0;				//	write offset
	int tempSize	=	0;				//	temp variable off size be writed
	int coun		=	0;				//	temp variable
	int sizeCounter	=	size;			//	counter of bytes need write
	char address[BLOCK_ADSRESS_SIZE];	//	temp Address variable
	char tempBuf[BLOCK_SIZE+1];			//	temp buffer variable


	if(checkFileDescUsage(fs,fd) != -1)				//	check corection
		InodeID 	= 	fs->fileTable[fd].inode;	//	set inode
	else
	{
		privateWriteLog(fs,ERR_WRITE_CLOSED);		//	write erro

		//	check if inode exist
		if(fs->inodeList[InodeID].inUse != 1)
				privateWriteLog(fs,ERR_INCORECT_INODE);

		privateWriteLog(fs,ERR_ON_WRITE);			//	write error
		return(-1);									//	return error
	}

	///			While have data to write
	while(sizeCounter>0)
	{
		memset(tempBuf,'+',BLOCK_SIZE);				//	prepare memory
		//	get block and get offset inside off block
		need_b 			=	fs->inodeList[InodeID].fileSize/BLOCK_SIZE;
		writeOffset		=	fs->inodeList[InodeID].fileSize%BLOCK_SIZE;
		tempSize 		= 	BLOCK_SIZE - writeOffset;

		//	Here is calculation fix of offset in block
		if(sizeCounter <  BLOCK_SIZE)
			tempSize= sizeCounter;
		else
			tempSize = BLOCK_SIZE;
		//	Here is calculation fix of offset in block
		if(writeOffset > 0 && tempSize >=BLOCK_SIZE)
			tempSize 		= 	BLOCK_SIZE - writeOffset;

		//	Prepare write data into block by copy needed data to temp buffer
		for(coun=0;coun<tempSize;coun++)
			tempBuf[coun] = buffer[size-sizeCounter+coun];


		if(need_b < DIRECT_ENTRIES)		//	writing to 3 first blocks
		{
			if(writeOffset == 0)		//	allocate block if need
				fs->inodeList[InodeID].directBlocks[need_b]=AllocBlock(fs);
			//	Call function write to block
			writeToBlock(fs,fs->inodeList[InodeID].directBlocks[need_b],
					tempBuf,writeOffset,tempSize);
			fs->inodeList[InodeID].fileSize += tempSize;	//	update size

		}
		else if(need_b >= DIRECT_ENTRIES && need_b < DOUBLE_START)
		{		/* 	Here is single block writing*/
			int BlockID = 0;

			//	if the block for single enties wasnt allocated, allocate him
			if(need_b == DIRECT_ENTRIES && writeOffset == 0)
				fs->inodeList[InodeID].singleIndirectBlocks[0]=AllocBlock(fs);

			if(writeOffset == 0)
			{
				BlockID = AllocBlock(fs);	//	allocate block in second level
				intToChar(address,BlockID);	//	convert address to int
				writeToBlock(fs,fs->inodeList[InodeID].singleIndirectBlocks[0],
						address,(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE,
						BLOCK_ADSRESS_SIZE);
			}
			else
			{	//	get need block on tihrt level
				BlockID = getAddress(fs,
						fs->inodeList[InodeID].singleIndirectBlocks[0],
						(need_b-DIRECT_ENTRIES)*BLOCK_ADSRESS_SIZE);
			}
			//	Write data and update size
			writeToBlock(fs,BlockID,tempBuf,writeOffset,tempSize);
			fs->inodeList[InodeID].fileSize += tempSize;
		}
		else if(need_b>=DOUBLE_START && need_b < BLOCKS_PER_INODE)
		{
			/* * 	Here is double block writing*/
			//	Get id of block on second level
			int SecendLevelID =(need_b-DOUBLE_START)/BLOCK_ADSRESS_SIZE ;
			int SecendLevelNewIDBlock = 0;				//	if need
			int secondLVLentry = 0;						//	temp variable

			//	if It is starting fill double block allocate first level block
			if(need_b == DOUBLE_START && writeOffset == 0)
				fs->inodeList[InodeID].doubleIndirectBlocks[0]=AllocBlock(fs);

			//	if need new block on second level - allocate him
			if( (need_b - (DOUBLE_START))%BLOCK_ADSRESS_SIZE ==0
					&& writeOffset == 0)
			{
				SecendLevelNewIDBlock = AllocBlock(fs);	//	alloc block
				intToChar(address,SecendLevelNewIDBlock);
				writeToBlock(fs,fs->inodeList[InodeID].doubleIndirectBlocks[0],
			address,SecendLevelID*BLOCK_ADSRESS_SIZE,BLOCK_ADSRESS_SIZE);
			}
			//	Get address of second level block
			secondLVLentry = getAddress(fs,
				fs->inodeList[InodeID].doubleIndirectBlocks[0],SecendLevelID);
			int offset_in2_lvl = (need_b - DOUBLE_START)%BLOCK_ADSRESS_SIZE ;
			int newBlcokID = 0;
			//	Allocating data block - Third levlel
			if(writeOffset == 0)
			{
				newBlcokID = AllocBlock(fs);		//	allocate data block
				intToChar(address,newBlcokID);		//	convert int to char
				//	write new adress
				writeToBlock(fs,secondLVLentry,address,
						offset_in2_lvl*BLOCK_ADSRESS_SIZE,BLOCK_ADSRESS_SIZE);

			}
			else	//	just get the adreess
				newBlcokID = getAddress(fs,secondLVLentry,offset_in2_lvl);
			//	Write data to block
			writeToBlock(fs,newBlcokID,tempBuf,writeOffset,tempSize);
			fs->inodeList[InodeID].fileSize += tempSize;	//	size
		}
		else
			privateWriteLog(fs,ERR_FILE_FULL);		//	file is full

		sizeCounter -=tempSize;						//	update counter
	}

	return(-1);										//	return error

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
//	Function wich print all error
//	Function get pointer to main data structure
void printLog(fs_t *fs)
{
	int coun = 0;						//	temp variable

	//	For each entry in array
	for(coun=0;coun<MAX_ERRORS;coun++)
	{
		if(fs->lastErrors[coun])		//	check if entry have error id
			printf("Error %d \n",fs->lastErrors[coun]);	//	print id
	}
}

//=============================================================================
//	Function wich write to log in our file system last errors
//	Function get pointer to main data structure and error id
void privateWriteLog(fs_t *fs,const int errorID)
{
	if(fs->lastErrEntry == MAX_ERRORS)			//	calculate next entry
		fs->lastErrEntry = 0;					//	set next entry

	fs->lastErrors[fs->lastErrEntry] = errorID;	//	set error ID
	fs->lastErrEntry++;							//	change next entry

}

//=============================================================================
/*
 * 		Function wich allocate block and set need variables to know if block
 * allocated and where and how.
 * 		Function get pointer to main data structure
 * 		Function return block ID if success or -1 if fail
 */
int AllocBlock(fs_t *fs)
{
	int ret_val = findNotUsedBitMap(fs);		//	find free block

	if(ret_val>=0)								//	check value
	{
		fs->Bitmap[ret_val] = 1;				//	update bitmap
		return(ret_val);						//	return value
	}

	privateWriteLog(fs,ERR_BITMAPS_FULL);		//	write error

	return(-1);									//	return error
}

//=============================================================================
//	Function for check file descriptor boundary
//	Function get file descriptor and check if the file descriptor have right
//	boundary value and also get pointer to main data structure
//	on good return geted value on fail return -1
int checkFileDesc(fs_t *fs,const int fd)
{
	if(fd>=0 && fd < NR_INODES)					//	check boundary
		return(fd);

	privateWriteLog(fs,ERR_INCORECT_FD);		//	write log

	return(-1);									//	return
}

//=============================================================================
//	Function wich check if the file descriptor wich geted in second
//	parameter can be used, also get pointer to main data structure
//	Return fd on good or -1 on fail
int checkFileDescUsage(fs_t *fs,const int fd)
{

	//	Call to check boundary and check if opened
	if(checkFileDesc(fs,fd) != -1 && fs->fileTable[fd].inUse == 1 )
		return(fd);

	return(-1);									//	rerurn error

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
	if(checkFileDescUsage(fs,fileHandle) >= 0
			&& fs->fileTable[fileHandle].inUse)
	{
		fs->fileTable[fileHandle].inUse 		= 0;
		fs->fileTable[fileHandle].fd   			= 0;
		fs->fileTable[fileHandle].inode 		= 0;
		fs->fileTable[fileHandle].fileOffset   	= 0;
		memset(fs->fileTable[fileHandle].filename,'\0',MAX_FILE_NAME);
		return(0);
	}
	else
		privateWriteLog(fs,ERR_CLOSE_CLOSED_F);	//	write error

	return(-1);
}

//=============================================================================
/*
 *	Function wich find file Inode by name used in open file
 *	Function get pointer to main data base structure
 *	Function rerurn Inode ID if success find or -1 on fail
 */
int findFileNode(fs_t *fs,char *fileName)
{
	char fileData[MAX_FILE_SIZE];		//	buffer for all data in dir
	char buffer[BLOCK_SIZE];			//	buffer for each block
	int tempSize 	= 	0;				//	temp variable
	int coun 		=	0;				//	temp variable
	struct DirEntry tempDirEntry;		//	Struct of direntry
	int fileCounter	=	0;				//	temp variable

	if(strlen(fileName) < 1)			//	check len of string
		return(-1);
	//	Get all data in directory
	fsReadFileAll(fs,ROOT_DIRECTORY_HANDLE,fileData,&tempSize);

	while(tempSize>0)
	{
		//	Copy data
		for(coun = 0; coun < BLOCK_SIZE;coun++)
			buffer[coun] = fileData[fileCounter*BLOCK_SIZE+coun];

		memcpy(&tempDirEntry,buffer,BLOCK_SIZE);	//	copy memory

		//	check if the name
		if(strcmp(tempDirEntry.filename,fileName) == 0)
			return(tempDirEntry.inode);

		fileCounter++;
		tempSize-=BLOCK_SIZE;			//	update temp variable
	}

	return(-1);

}

//=============================================================================
/*
 *		Function for format file system
 *		Function get pinter to main dta structure
 *		Function return 0 on seccess or -1 on fail
 */
int fsFormat(fs_t *fs)
{
	int coun = 0;						//	temp variable
	char tmpBuffer[BLOCK_SIZE];			//	Create temp buffer
	int res= 0;							//	temp value

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

	memset(tmpBuffer,'-',BLOCK_SIZE);	//	write some information to tmpBLock
	lseek(fs->fd,DATA_START,SEEK_SET);	//	lseek into data sector

	for(coun = 0 ; coun < NR_BLOCKS;coun++)
	{

		res= write(fs->fd,tmpBuffer,BLOCK_SIZE);
		if(res == -1)
		{
			perror("Cannot write to simulation file.\n");
			fsUnMount(fs);								//	clear memory
			exit(EXIT_FAILURE);							//	exit
		}
	}

	return(0);
}

//=============================================================================
/*
 *	Function wich get pointer to main data structure and can check
 *	if need format file system. This not work so good but not used any
 *	aditional variables ot data structure or any space on disk.
 *	This function can be improved by adding anothers check
 *	For example checks wich do fdsk - but we not learn this.
 *	On good return 1 on fail 0
 */
int checkFileSystem(fs_t *fs)
{
	if(fs->inodeList[ROOT_DIRECTORY_HANDLE].inUse == 1)
		return(1);
	else
		return(0);

}
//=============================================================================
/*
 *	Function wich mount file system	And return pointer to main data structure
 */
fs_t *fsMount()
{
	int coun 	= 0;
	fs_t *ret 	= NULL;

	ret = (fs_t*)malloc(sizeof(fs_t));
	if(ret == NULL)									//	check allocating
	{
		perror("Can not  allocate memory in fsMount\n");
		exit(EXIT_FAILURE);							//	ret error end exit
	}

	ret->fd = open(FILENAME,O_RDWR );				//	open file
	if(ret->fd == -1)
	{
		perror("Cannot open simulation file.\n");
		fsUnMount(ret);								//	clear memory
		exit(EXIT_FAILURE);							//	exit
	}

	//	go to section where the data start
	ret->filesize = lseek(ret->fd,DATA_START,SEEK_SET);
	//	create map to Bitmaps and Inodes
	ret->source = mmap(0,ret->filesize,
			PROT_READ | PROT_WRITE,MAP_SHARED,ret->fd,0);
	//	Check if map created
 	if(ret->source == (char *) -1)
 	{
  		perror("Can not open map file\n");
		exit(EXIT_FAILURE);							//	exit

  	}
 	//	Start copy bitmaps from memory
 	for(coun=0;coun<NR_BLOCKS;coun++)
		ret->Bitmap[coun] = ret->source[coun]- '0';

	PrepareAllInodesOnMount(ret);					//	load inodes

	//	Check if file system formated
	if(checkFileSystem(ret))
		ret->fsInitialized = 1;			//	if formated
	else
	{
		privateWriteLog(ret,ERR_NEED_FORMAT);
		ret->fsInitialized = 0;			//	need format
	}
	//	set name of root dir
	memcpy(&ret->fileTable[ROOT_DIRECTORY_HANDLE].filename,
			ROOT_DIR_NAME,sizeof(ROOT_DIR_NAME));
	//	prepare root dir
	ret->fileTable[ROOT_DIRECTORY_HANDLE].inUse = 1;
	ret->fileTable[ROOT_DIRECTORY_HANDLE].inode = ROOT_DIRECTORY_HANDLE;
	ret->fileTable[ROOT_DIRECTORY_HANDLE].fd = 0;
	ret->fileTable[ROOT_DIRECTORY_HANDLE].fileOffset =
								ret->inodeList[ROOT_DIRECTORY_HANDLE].fileSize;


	ret->lastErrEntry =	0;		//	For errors array
	//	Prepare array of errors
	for(coun=0;coun<MAX_ERRORS;coun++)
		ret->lastErrors[coun] = 0;

	return(ret);				//	return pointer to main data structure
}

//=============================================================================
/*
 *		Function wich provide onmount operation
 *		Function get poiunter to main data structure
 */
int fsUnMount(fs_t *fs)
{
	if(fs->fd > 0)
	{
		SaveToFS_BitMap_INODES(fs);				//	save all bitmaps in memory
		//	Close map
		if(munmap(fs->source, fs->filesize) == -1)
		{
			perror("Error un-mmapping the file\n");
			exit(EXIT_FAILURE);
		}
		close(fs->fd);								//	close file
	}

	free(fs);									//	clear used mem

	return(0);									//	return 0
}

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


	if(sizeof(fileName) >= MAX_FILE_NAME || sizeof(fileName) < 1)
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
			privateWriteLog(fs,ERR_ALL_INODES_FULL);
			return(-1);
		}
		return(ret_FD);						//	return file handle
	}
	else
	{
		privateWriteLog(fs,ERR_NEED_FORMAT);
		return(-1);
	}
}

//=============================================================================
/*
 * 	Function wich get pinter to main data structure, block id where need write
 * new data which contained in next parameter in buffer, and get offset
 * in the this block and also size wich need write
 */
void writeToBlock(fs_t *fs,const int blockID,char *buffer,
					const int offSet,const int size)
{
	int writeRes = 0;		//	write operation result
	//	Do lseek in file
	lseek(fs->fd,DATA_START+blockID*BLOCK_SIZE+offSet,SEEK_SET);
	writeRes = write(fs->fd,buffer,size);		//	write data

	//	Check if write success
	if(writeRes == -1)
		privateWriteLog(fs,ERR_OS_WRITE_BAD);	//	write error

}

//=============================================================================
/*
 * 	Function wich get pinter to main data structure, buffer to data
 * thats mean the readed data be puted in to thus buffer and block id which
 * need to read
 */
void readBlockData(fs_t *fs,char *dataBuff,const int blockID)
{
	int readRes = 0;		//	read operation result
	//	Do lseek for read in file
	lseek(fs->fd,DATA_START+blockID*BLOCK_SIZE,	SEEK_SET);
	readRes =read(fs->fd,dataBuff,BLOCK_SIZE);				//	read data

	//	Check if read success
	if(readRes == -1)
		privateWriteLog(fs,ERR_OS_READ_BAD);				//	write error

}

//=============================================================================
/*
 * 	Function wich get pinter to main data structure block id and nunber of
 * address in block
 * Return address(int) writed there
 */
int getAddress(fs_t *fs,const int blockID,const int AdressSET)
{

	char address[BLOCK_ADSRESS_SIZE];				//	temp for address
	int returnAdr = 0;								//	return value
	int readRes = 0;								//	proced

	//	Lseek in file
	lseek(fs->fd,
		DATA_START+blockID*BLOCK_SIZE+AdressSET*BLOCK_ADSRESS_SIZE,	SEEK_SET);

	readRes = read(fs->fd,address,BLOCK_ADSRESS_SIZE);	//	read data

	//	Check if read success
	if(readRes == -1)
		privateWriteLog(fs,ERR_OS_READ_BAD);		//	write error
	else
		forCharsToInt(address,&returnAdr);			//	convert address to int

	return(returnAdr);								//	return address

}

//=============================================================================
/*
 *		Function for create new file system file
 *		Function get New system file name.
 *		Function return 0 on success
 */
int fsCreateFileSystem(char *filename)
{
	//	Calculate file size offset
	int fileSize 	= 	NR_BLOCKS+NR_INODES*NODE_SIZE+NR_BLOCKS*BLOCK_SIZE;
	int fd			=	0;	//	file descriptor


	if(creat(filename,0600) == -1)						//	Create file
	{
		perror("Cannot create new simulation file.\n");
		exit(EXIT_FAILURE);
	}

	fd = open(FILENAME,O_RDWR);							//	OPen file

	if(fd == -1)
	{
		perror("Cannot open simulation file.\n");
		exit(EXIT_FAILURE);
	}


	lseek(fd,fileSize,SEEK_SET);						//	go to end
	if(write(fd,"-",1) == -1)
	{
		perror("Cannot write to simulation file.\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Created simulation file[%s], of size %d\n",filename,fileSize);

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
void PrintStatistic(fs_t *fs)
{

	int coun = 0;					//	temp variable

	//	For each block print if the block used ot not
	printf("\nInformation about bitmaps:\n");
	for(coun=0;coun< NR_BLOCKS;coun++)
	{
		printf("%d",fs->Bitmap[coun]);
		//	Print the information in few lines for better understeind
		if((coun+1)%NR_INODES == 0)
			printf("\n");

	}
	printf("\n");

	char fileData[MAX_FILE_SIZE];		//	Place to get all data in file
	char buffer[BLOCK_SIZE];			//	BLock data
	int tempSize 		= 	0;			//	temp variable
	int fileCounter 	= 	0;			//	Counter of files in directory
	struct DirEntry tempDirEntry;

	fs->fileTable[ROOT_DIRECTORY_HANDLE].fileOffset = 0;
	//	Read all data in file-directory
	fsReadFileAll(fs,ROOT_DIRECTORY_HANDLE,fileData,&tempSize);
	printf("Information about files in root directory:\n");
	while(tempSize>0)
	{
		//	Copy data(block) into temp buffer
		for(coun = 0; coun < BLOCK_SIZE;coun++)
			buffer[coun] = fileData[fileCounter*BLOCK_SIZE+coun];

		fileCounter++;					//	update file counter

		memcpy(&tempDirEntry,buffer,BLOCK_SIZE);	//	copy memory
		//	Print information to user
		printf("%s Inode:[%d] Size:[%d] Blocks[",
				tempDirEntry.filename,tempDirEntry.inode,
				fs->inodeList[tempDirEntry.inode].fileSize);
		//	Print blocks of used by inode
		PrintAllFileBlocks(fs,tempDirEntry.inode);
		printf("]\n");
		 tempSize-=BLOCK_SIZE;			//	decrase size wich need to read

	}

}
//=============================================================================
/*
 * 	Function wich print per inode him block wich used on file system
 * Function get pointer to main data structure and inode id
 * The function must be called only from print statistic becose no any
 * check of indoe corect
 */
void PrintAllFileBlocks(fs_t *fs,const int inode)
{

	struct FileDescriptor fd;
	fd.fileOffset = 0;
	int InodeID 	= 	inode;	//	Inode of block
	int need_b 		=	fd.fileOffset/BLOCK_SIZE;//Block need
	int adrINT 		= 	0;							//	variable see next

	//	Check if we over the file size trying to read
	while(fd.fileOffset < fs->inodeList[InodeID].fileSize)
	{
		need_b 		=	fd.fileOffset/BLOCK_SIZE;//Block need

		if(need_b < DIRECT_ENTRIES)
			printf("%d|",fs->inodeList[InodeID].directBlocks[need_b]);
		else if(need_b >= DIRECT_ENTRIES && need_b < DOUBLE_START)
		{

			if(need_b == DIRECT_ENTRIES)
				printf("%d|",fs->inodeList[InodeID].singleIndirectBlocks[0]);
			/* 	Here is single block reading*/
			adrINT = getAddress(fs,
					fs->inodeList[InodeID].singleIndirectBlocks[0],
						(need_b-DIRECT_ENTRIES));
			printf("%d|",adrINT);
		}
		else if(need_b>=DOUBLE_START && need_b < BLOCKS_PER_INODE)
		{
			//	Get id of block on second level
			int AddressSET = (need_b - DOUBLE_START)	/BLOCK_ADSRESS_SIZE ;
			if(need_b%DOUBLE_START==0)
				printf("%d|",fs->inodeList[InodeID].doubleIndirectBlocks[0]);

			adrINT = getAddress(fs,
					fs->inodeList[InodeID].doubleIndirectBlocks[0],AddressSET);
			if(AddressSET == 0)
				printf("%d|",adrINT);
			//	calculate offset in side of second level block
			AddressSET = (need_b -DOUBLE_START)%BLOCK_ADSRESS_SIZE ;
			adrINT = getAddress(fs,adrINT,AddressSET);
			printf("%d|",adrINT);

		}
		fd.fileOffset+=BLOCK_SIZE;

	}

}

//=============================================================================
//=============================================================================
//=============================================================================
