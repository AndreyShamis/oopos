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
	
	printf("Data start from %d\n",DATA_START);
	//char data[BLOCK_SIZE];
	
	//-------------------------------------------------------------------------
	//	Proverochniy block dlya char to int i naoborot
/*	int lol=0;
	char try[4] = "0234";
	forCharsToInt(try,&lol);

	printf("The number : %d.\n",lol);

	lol=23;
	intToChar(try,lol);
	printf("The string : %s.\n",try);
*/
	//-------------------------------------------------------------------------


	int h1=0,h2=0;
	
	int size=0;
	
	//MOUNT
	fs = fsMount();
	
	//	First Format
	int res = 0;
	res = fsFormat(fs);


	//	Create two test files
	
	h1 = fsCreateFile(fs,"12.txt");

	h2 = fsCreateFile(fs,"2.txt");
	fsCreateFile(fs,"3.txt");
	fsCreateFile(fs,"4.txt");
	fsCreateFile(fs,"5.txt");
	fsCreateFile(fs,"6.txt");
	fsCreateFile(fs,"7.txt");
	fsCreateFile(fs,"8.txt");
	fsCreateFile(fs,"9.txt");
	//printf("Created files FD1 %d - FD2 %d\n", h1,h2);
	/*
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
	*/


	//	Print staticstic
	//PrintStatistic(fs);

	fsPrintRootDir(fs);
	//unmount

	res = fsUnMount(fs);

	printf("Bye Bye\n");
	return(EXIT_SUCCESS);
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
//=============================================================================
//=============================================================================
