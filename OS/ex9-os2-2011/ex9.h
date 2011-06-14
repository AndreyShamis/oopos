/*
 * 	This file provide header file for main program
 * Which provide tools for simulation of work wich file system
 * in computer.
 *
 */

#ifndef _EX9			//	Define Header Off ex9
#define _EX9
//=============================================================================
//	Include Section
#include <stdio.h>		//	standrard I/O
#include <stdlib.h>		//	used for EXIT_SUCCESS
#include <string.h>		//	used in strlen
#include <unistd.h>
#include <math.h>		//	posible for use in pow

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>	//	for use mmap function
#include <fcntl.h>

#include "defines.inc.h"		//	inlude globals- fefines
#include "errors.inc.h"			//	include errors page
#include "structures.inc.h"		//	include structures

typedef struct fs fs_t;

//=============================================================================
/*		Function which serach in struct which Inode not in use.
 * 	Geting pointer to main data base structure.
 * Return n>0 if finded somthing ot -1 if not */
int findNotUsedIndoe(fs_t *fs);
//=============================================================================
/*		Function wich looking in main data base wich bitmap is in not use.
 * 		Get pointer to main data base.
 * 		Return n>=0 if found; -1 if not found*/
int findNotUsedBitMap(fs_t *fs);
//=============================================================================
/*		Function for convert char(string) to int
 * 	Geting String wich need convert and pointer to int in wich be returned
 * 	the value. */
void forCharsToInt(char val[BLOCK_ADSRESS_SIZE],int *retValue);
//=============================================================================
/*		Function for convert int to char
 * 	Geting integer wich need convert and char in wich be retuned
 * converted value*/
void intToChar(char val[BLOCK_ADSRESS_SIZE],const int valInt);
//=============================================================================
/*
 * 		Function wich read from file into buffer
 * 	Getting file description , size of bytes need to read, pointer to data
 * 	structure.
 * 		Return in buffer pointer string readed, and returned value it is
 * 	size of readed bytes*/
int fsReadFile(fs_t *fs,int fd,char *buffer,int readSize);
//=============================================================================
/*
 * 		Function for reading only one block each call
 * 	Function geting pointer to data structure wich used in our program,
 * 	File discriptor of file wich we wont to read, and buffer.
 * 		Return: funvtion return in buffer pointer the information readed
 * 	from block, and also return the size wich was readed, usualy it
 * 	is BLOCK_SIZE but if not success to read- it is happen where trying
 * 	to read more then file have so return 0 or on error -1*/
int fsReadFileBlock(fs_t *fs,int fd,char *buffer);
//=============================================================================
/*
 * 		Function wich print statistic about program simulation.
 * 	Get pointer to main data base.
 * 	Print information such:
 * 	-	Status of bitmap usage
 * 	-	Files in directory(we have only one)
 * 	-	Size of each file
 * 	-	And list of block for each file*/
void PrintStatistic(fs_t *fs);
//=============================================================================
/*
 * 		Function which serach in struct which fileTable not in use.
 * 	Geting pointer to main data base structure.
 * Return n>0 if finded somthing ot -1 if not*/
int findNotUsedFD(fs_t *fs);
//=============================================================================
/*
 *		Function for create file in our file system
 *	Function get pointer main data structure and the name of new file
 *	Return file desctiptor of new file or -1 if not success create file*/
int fsCreateFile(fs_t *fs,char *fileName);
//=============================================================================
/*
 *		Function for open file
 *		Function Get pointer to main structure of our program and file name
 *		wich need open
 *		Return file descriptor if success open file or -1 on fail*/
int fsOpenFile(fs_t *fs,char *fileName);
//=============================================================================
/*
 *		Function wich close open file.
 *		Function get pointer to our main data structure and file handle
 *		Function return 0 on success or -1 on fail */
int fsCloseFile(fs_t *fs,int fileHandle);
//=============================================================================
/*
 *		Function wich write data into file
 *		Function get pointer to main data structure,file descriptor of file
 *	in wich we wont to write data, buuffer contein the data wich we want to
 *	in write and size of data wich be writed
 *		Function return size of writed data  or -1 on fail */
int fsWriteFile(fs_t *fs,int fd,const char *buffer,const int size);
//=============================================================================
/*
 * 		Function wich reading all data in file
 * 	Function get pointer to main data structure , file descriptor of file
 * wich we wont to read, also buffer for data (must be in size of file), and
 * in last we get pointer
 * 	Function return 0 on success or -1 on fail */
int fsReadFileAll(fs_t *fs,int fd,char *buffer,int *readSize);
//=============================================================================
/*
 * 		Function wich allocate block and set need variables to know if block
 * allocated and where and how.
 * 		Function get pointer to main data structure
 * 		Function return block ID if success or -1 if fail*/
int AllocBlock(fs_t *fs);
//=============================================================================
/*
 *		Function wich provide onmount operation
 *		Function get poiunter to main data structure*/
int fsUnMount(fs_t *fs);
//=============================================================================
/*
 * 		Function wich print all direcotory entry - all files
 * 		Function get pointer to main data structure */
void fsPrintRootDir(fs_t *fs);
//=============================================================================
/*
 *		Function wich load all inodes from file system from inode sector
 *		Function get pointer to main data structure */
void PrepareAllInodesOnMount(fs_t *fs);
//=============================================================================
/*
 *		Function for create new file system file
 *		Function get New system file name.
 *		Function return 0 on success*/
int fsCreateFileSystem(char *filename);
//=============================================================================
/*
 *		Function for saving bit maps(coverting to int) and saving indes
 *		without converting
 *		Function get pointer to main data structure */
void SaveToFS_BitMap_INODES(fs_t *fs);
//=============================================================================
/*
 *		Function for format file system
 *		Function get pinter to main dta structure
 *		Function return 0 on seccess or -1 on fail*/
int fsFormat(fs_t *fs);
//=============================================================================
//	Function wich write to log in our file system last errors
//	Function get pointer to main data structure and error id
void privateWriteLog(fs_t *fs,const int errorID);
//=============================================================================
//	Function for check file descriptor boundary
//	Function get file descriptor and check if the file descriptor have right
//	boundary value and also get pointer to main data structure
//	on good return geted value on fail return 0
int checkFileDesc(fs_t *fs,const int fd);
//=============================================================================
//	Function wich check if the file descriptor wich geted in second
//	parameter can be used, also get pointer to main data structure
//	Return fd on good or 0 on fail
int checkFileDescUsage(fs_t *fs,const int fd);
//=============================================================================
//	Function wich print all error
//	Function get pointer to main data structure
void printLog(fs_t *fs);
//=============================================================================
/*
 *	Function wich find file Inode by name used in open file
 *	Function get pointer to main data base structure
 *	Function rerurn Inode ID if success find or -1 on fail */
int findFileNode(fs_t *fs,char *fileName);
//=============================================================================
/*
 * 	Function wich get pinter to main data structure, block id where need write
 * new data which contained in next parameter in buffer, and get offset
 * in the this block and also size wich need write */
void writeToBlock(fs_t *fs,const int blockID,char *buffer,
					const int offSet,const int size);
//=============================================================================
/*
 * 	Function wich get pinter to main data structure block id and nunber of
 * address in block
 * Return address(int) writed there */
int getAddress(fs_t *fs,const int blockID,const int AdressSET);
//=============================================================================
/*
 * 	Function wich get pinter to main data structure, buffer to data
 * thats mean the readed data be puted in to thus buffer and block id which
 * need to read*/
void readBlockData(fs_t *fs,char *dataBuff,const int blockID);
//=============================================================================
/*
 *Function wich mount file system And return pointer to main data structure */
fs_t *fsMount();
//=============================================================================
/*
 * 	Function wich print per inode him block wich used on file system
 * Function get pointer to main data structure and inode id
 * The function must be called only from print statistic becose no any
 * check of indoe corect */
void PrintAllFileBlocks(fs_t *fs,const int inode);
//=============================================================================
/*
 *	Function wich get pointer to main data structure and can check
 *	if need format file system. This not work so good but not used any
 *	aditional variables ot data structure or any space on disk.
 *	This function can be improved by adding anothers check
 *	For example checks wich do fdsk - but we not learn this.
 *	On good return 1 on fail 0 */
int checkFileSystem(fs_t *fs);

#endif
//=============================================================================
//=============================================================================
//=============================================================================

