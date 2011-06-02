/*
 * 	This file provide header file for main program
 * Which provide tools for simulation of work wich file system
 * in computer.
 *
 */


//=============================================================================
//	Include Section
#include <stdio.h>		//	standrard I/O
#include <stdlib.h>		//	used for EXIT_SUCCESS
#include <string.h>

//=============================================================================
//	Define section

#define ROOT_DIRECTORY_HANDLE 0 // 	the root ('/') dir handle

#define BLOCK_SIZE 16
#define BLOCK_ADSRESS_SIZE 4

#define MAX_FILE_NAME 12
#define DIRECT_ENTRIES 3
#define SINGLE_INDIRECT_ENTRIES 1
#define DOUBLE_INDIRECT_ENTRIES 1

#define ENTRIES_PER_BLOCK (BLOCK_SIZE/BLOCK_ADSRESS_SIZE)

#define NR_BLOCKS 3712
#define NR_INODES 128

//	maximum blocks held by the single/double indirect entries
#define SINGLE_INDIRECT_BLCOKS ENTRIES_PER_BLOCK
#define DOUBLE_INDIRECT_BLOCKS (ENTRIES_PER_BLOCK*ENTRIES_PER_BLOCK)

//	maximum blocks an inode can hold
#define BLOCKS_PER_INODE (DIRECT_ENTRIES \
				+ SINGLE_INDIRECT_ENTRIES*SINGLE_INDIRECT_BLCOKS \
				+ DOUBLE_INDIRECT_ENTRIES+DOUBLE_INDIRECT_BLOCKS)

//	maximum file size in bytes
#define MAX_FILE_SIZE (BLOCKS_PER_INODE*BLOCK_SIZE)

//	number of bits per block
#define BLOCK_BITS (BLOCK_SIZE*sizeof(char))

#define BLOCKS_PEER_INODE 10



//=============================================================================
struct FileDescriptor
{
	int 	inUse;
	int 	fd;
	char 	filename[MAX_FILE_NAME];
	int 	inode;
	int		fileOffset;
};

struct DirEntry
{
	char 	filename[MAX_FILE_NAME];
	int 	inode;
};

struct FSInode
{
	int 	inUse;
	int 	fileSize;
	int 	directBlocks[DIRECT_ENTRIES];
	int 	singleIndirectBlocks[SINGLE_INDIRECT_ENTRIES];
	int 	doubleIndirectBlocks[DOUBLE_INDIRECT_ENTRIES];
};

struct fs
{
	//	Tell us which blocks are occupaied
	int Bitmap[NR_BLOCKS];
	//	map the inodes on the disk
	struct FSInode inodeList[NR_INODES];
	//	pointer to the first Inode (the first directory)
	struct FSInode *pRootInode;
	//	holds the open file descriptor
	struct FileDescriptor fileTable[NR_INODES];
	//	=	0 if initializes,i otherwise
	int fsInitialized;
	//	fd of our virtual HSS
	FILE *fd;
};

typedef struct fs fs_t;

//=============================================================================
int fsFormat(fs_t *fs,char *filename)
{
	return(0);

}

//=============================================================================
fs_t *fsMount(char *filename)
{
	fs_t *ret = NULL;

	return(ret);
}
//=============================================================================
int fsUnMount(fs_t *fs)
{
	return(0);
}

//	Blcok of CREATE/OPEN/CLOSE
//=============================================================================
int fsCreateFile(fs_t *fs,char *fileName)
{

	return(0);
}
//=============================================================================
int fsOpenFile(fs_t *fs,char *fileName)
{

	return(0);
}
//=============================================================================
int fsCloseFile(fs_t *fs,int fileHandle)
{

	return(0);
}

//	BLOCK OF Write/READ
//=============================================================================
int fsWriteFile(fs_t *fs,int fd,const char *buffer,const int size)
{
	return(0);
}
//=============================================================================
int fsReadFile(fs_t *fs,int fd,char *buffer,int *readSize)
{
	return(0);
}

//=============================================================================
void fsPrintRootDir(fs_t *fs)
{

	printf("The directory is <> and contain:\n");

	printf("\n");
}
//=============================================================================
//=============================================================================
//=============================================================================
