#include "ex9.h"

#define FILENAME "testFS.dat"






int main()
{
	fs_t	*fs;
	
	char data[BLOCK_SIZE];
	
	int h1,h2;
	
	int size;
	
	//MOUNT
	
	fs = fsMount(FILENAME);
	
	//	First Format
	
	res = fsFormat(fs,FILENAME,size);
	printf("File system size = %d\n",size);
	
	//	Create two test files
	
	h1 = fsCreateFile(fs,"text1.txt");
	h2 = fsCreateFile(fs,"text2.txt");
	
	char blockSizeData[BLOCK_SIZE] = " I`am  001 file ";
	
	size = strlen(blockSizeData) +1;
	
	//write
	
	for(int t=0;t<BLOCKS_PEER_INODE;t++)
	{
		sprintf(blockSizeData+size-3,"%2d",t);
		blockSizeData[size-1]=0;
		res =fsWriteFile(fs,h1,blockSizeData,size);
	}
	
	//read
	char zeros[110];
	
	memset(zeros,0xFF,sizeof(zeros));
	res= fsReadFile(fs,h2,zeros,100,size);


	//unmount

	res = fsUnMount(fs);
}

