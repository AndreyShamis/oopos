/*
 * EX9:: File sistem manipulations
 * ===========================================================================
 * Writen by: Andrey Shamis,  id: 321470882, login: andreysh
 * and:       Ilia Gaisinsky, id: 309480051, login: iliaga
 * ===========================================================================
 *
 * ===========================================================================
	This program provide tools for manipulations with file system

	For compile just run:

		make

	for run the program use next comand line

		./ex9
*/
#include "ex9.h"

//=============================================================================
//=============================================================================
int main()
{
	fs_t	*fs;			//	pointer to main data structure
	int h1=0,h2=0;			//	file handles
	int size=0;

	//MOUNT
	fs = fsMount();

	int res = 0;
	res = fsFormat(fs);


	//	Create two test files
	h1 = fsCreateFile(fs,"File 1.txt");
	h2 = fsCreateFile(fs,"File 2.txt");

	char blockSizeData[BLOCK_SIZE] = "I am file 001  ";

	size = strlen(blockSizeData)+1;

	//write
	int t=0;
	for(t=0;t<BLOCKS_PER_INODE;t++)
	{
		sprintf(blockSizeData+size-3,"%2d.",t);
		blockSizeData[size-1]=0;//'\0';
		res =fsWriteFile(fs,h2,blockSizeData,size);
	}
	//read
	char zeros[110];

	memset(zeros,0xFF,sizeof(zeros));
	res= fsReadFile(fs,h2,zeros,100);
	if(res>0)
		printf("Readed from file: \n%s \n", zeros);

	fsPrintRootDir(fs);				//	Print root dir entry

	//	Print staticstic
	PrintStatistic(fs);

	res = fsUnMount(fs);			//unmount

	return(EXIT_SUCCESS);			//	exit from program
}

//=============================================================================
//=============================================================================
//=============================================================================
