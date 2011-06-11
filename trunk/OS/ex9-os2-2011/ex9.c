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
	//fsCreateFileSystem(FILENAME);
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
	fsCreateFile(fs,"14.txt");

	fsCreateFile(fs,"16.txt");
	fsCreateFile(fs,"17.txt");
	fsCreateFile(fs,"18.txt");
	fsCreateFile(fs,"19.txt");
	fsCreateFile(fs,"110.txt");
	fsCreateFile(fs,"111.txt");
	fsCreateFile(fs,"112.txt");
	fsCreateFile(fs,"113.txt");
	fsCreateFile(fs,"114.txt");
	fsCreateFile(fs,"1114.txt");
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
	if(res>0)
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
	fsWriteFile(fs,h1,input3,110);
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
	printLog(fs);
	res = fsUnMount(fs);

	printf("Bye Bye\n");
	return(EXIT_SUCCESS);
}



//=============================================================================
//=============================================================================
//=============================================================================
