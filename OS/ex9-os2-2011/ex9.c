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

	printf("Blocks peer indoe %d\n",BLOCKS_PER_INODE);
	int h1=0,h2=0;
	
	int size=0;
	
	//MOUNT
	fs = fsMount();
	
	//	First Format
	int res = 0;
	res = fsFormat(fs);


	//	Create two test files
	
	h1 = fsCreateFile(fs,"1.txt");

	h2 = fsCreateFile(fs,"2.txt");

	fsCreateFile(fs,"3.txt");
	fsCreateFile(fs,"4.txt");
	fsCreateFile(fs,"5.txt");
	fsCreateFile(fs,"6.txt");
	fsCreateFile(fs,"7.txt");
	fsCreateFile(fs,"8.txt");
	fsCreateFile(fs,"9.txt");
	fsCreateFile(fs,"10.txt");
	fsCreateFile(fs,"11.txt");
	fsCreateFile(fs,"12.txt");
	fsCreateFile(fs,"13.txt");

	printf("Created files FD1 %d - FD2 %d\n", h1,h2);

//	char blockSizeData[BLOCK_SIZE] = "I` 001";
	char blockSizeData[BLOCK_SIZE] = "I am file 001  ";

	size = strlen(blockSizeData)+1;
	
	//write
	int t=0;
	printf("Size %d\n",size);
	for(t=0;t<BLOCKS_PER_INODE;t++)
	{
		//	TODO DELETE NEXT LINE
		//printf("\t # In for\n");
		sprintf(blockSizeData+size-3,"%2d.",t);
		blockSizeData[size-1]=0;//'\0';
		res =fsWriteFile(fs,h2,blockSizeData,size);
	}
	printf("End Write\n");
	//read
	//fsWriteFile(fs,h1,blockSizeData,size);
	char zeros[110];
	
	memset(zeros,0xFF,sizeof(zeros));
	res= fsReadFile(fs,h2,zeros,100);

	printf("Readed from file \n%s \n", zeros);


	printf("Print \n");
	int txtSize = sizeof("a2345678901234567890123456789012345678901234567\n");
	printf("TextSize : %d\n",txtSize);
	char input[60] = "a2345678901234567890123456789012345678901234567\n";
	fsWriteFile(fs,h1,input,txtSize-1);

//	char input[5] = "abcd";
//	fsWriteFile(fs,h1,input,4);

	/*
	printf("Print \n");
	 */

	char input1[81] = "Android Market web store now checks which apps are compatible with your\ndevices";
	fsWriteFile(fs,h1,input1,79);
	char input2[80] = "Andrey Shamis Was here , Whats Up Gaus? Hello! Bye...\nI`m HERE :-)";
	fsWriteFile(fs,h1,input2,66);
	char input3[400] = "Google has already made some tough moves to tackle fragmentation,\nbut it's clearly still wary of the problem.\nIt's just tweaked the Android Market web store to show users which apps are compatible with which of their gadgets. ";
	fsWriteFile(fs,h1,input3,180);
	/*
	char input1[81] = "Android Market web store now checks which apps are compatible with your devices";
	fsWriteFile(fs,h1,input1,80);
	char input2[80] = "Andrey Shamis Was here , Whats Up Gaus? Hello! Bye... I`m HERE :-)";
	fsWriteFile(fs,h1,input2,50);
*/
	char zeros2[250];

	memset(zeros,0xFF,sizeof(zeros2));
	res= fsReadFile(fs,h1,zeros2,249);

	printf("Readed from file \n%s \n", zeros2);
	//	Print staticstic
	//PrintStatistic(fs);
	//printf("Print dir\n");
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
//=============================================================================
//=============================================================================
