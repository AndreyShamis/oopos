struct DirEntry
{
	char 	filename[MAX_FILE_NAME];	//	file name
	int 	inode;						//	inode id of file name
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
	int 	inUse;					//	if descriptor use
	int 	fd;						//	file descriptor
	char 	filename[MAX_FILE_NAME];//	file name
	int 	inode;					//	inode of file
	int		fileOffset;				//	offset in file
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
	int 	lastErrors[MAX_ERRORS];	//	array of error happened
	int		lastErrEntry;			//	last error ID in array

};
