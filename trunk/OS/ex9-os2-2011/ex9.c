/*
 * 			ex9		::		File system simulation
 * Students:
 *
 *
 */
#include "ex9.h"
//=============================================================================

//=============================================================================



//=============================================================================
//=============================================================================
int main()
{
	fs_t	*fs;
	
	//char data[BLOCK_SIZE];
	
	int h1=0,h2=0;
	
	int size=0;
	
	//MOUNT
	fs = fsMount(FILENAME);
	
	//	First Format
	int res = 0;
	//res = fsFormat(fs,FILENAME);

	///////////////////// TODO Ubrat moyu dobavku  = %d byte
	printf("File system size = %d = %d byte\n",size,size/8);
	
	//	Create two test files
	
	h1 = fsCreateFile(fs,"text1.txt");
	h2 = fsCreateFile(fs,"text2.txt");
	
	char blockSizeData[BLOCK_SIZE] = " I`am  001 file ";
	
	size = strlen(blockSizeData) +1;
	
	//write
	int t=0;
	for(t=0;t<BLOCKS_PER_INODE;t++)
	{
		//	TODO DELETE NEXT LINE
		//printf("\t # In for\n");
		sprintf(blockSizeData+size-3,"%2d",t);
		blockSizeData[size-1]=0;
		res =fsWriteFile(fs,h1,blockSizeData,size);
	}
	
	//read
	char zeros[110];
	
	memset(zeros,0xFF,sizeof(zeros));
	res= fsReadFile(fs,h2,zeros,&size);


	//	Print staticstic
	PrintStatistic(fs);

	//unmount

	res = fsUnMount(fs);

	printf("Bye Bye\n");
	return(EXIT_SUCCESS);
}
//=============================================================================
//=============================================================================
//=============================================================================
