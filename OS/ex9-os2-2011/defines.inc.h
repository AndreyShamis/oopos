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

#define DOUBLE_START (DIRECT_ENTRIES+SINGLE_INDIRECT_BLCOKS)
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

//=============================================================================
