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
//=============================================================================

	Important functions

							* * *	
	fsWriteFile()	-	Function wich write data into file.
	Function get pointer to main data structure,file descriptor of file
in wich we wont to write data, buuffer contein the data wich we want to in 
write and size of data wich be writed .
	Function return size of writed data  or -1 on fail

 							* * *
	This function work very well with anu lentgh of data
be sended to function. If you write some string < BLOCK SIZE function write
the data to block and after this if you wont to write to this file more data
the finction will continue write the data to previous block when stoped write
and write exactly (block size - previous data len) and then will create new 
block and continue write there. So for use this function you can write in each
call how many you want chars. 

							* * *
	int fsCreateFileSystem(char *filename)
 	Function for create new file system file
Function get New system file name.Function return 0 on success.
 With this function you can create another file system .
So our programm provide tools to use many many file systems. For example you 
can ctreate two ot three file systems or even more

							* * *
	In Mount function we do not exactly fs->fsInitialized = 1 we have function
for check if file system is good and was formated or if need format file 
system. The function do simple check and not work so good(thats mean can be 
improved) but not used any aditional variables ot data structure or any space 
on disk. This function can be improved by adding anothers check. For example 
checks wich do fdsk - but we not learn this.

							* * *
	Our main data structure have array(size can be changed in define.inc.h)
for save errors happened in program such tryng write into full file or
read more then can and any others code errors in next you can read some type
of errors. And for more informattion look file error.inc.h.
If you want to see errors just use function printLog(fs) on the end of program
before you do UnMount operations.

//=============================================================================

	Important error codes

ERR_FILE_FULL 		1200	//	if tryed read/write more than can
ERR_READ_CLOSED		1201	//	if read closed file
ERR_WRITE_CLOSED	1202	//	if tryed write closed file
ERR_FILE_EXIST		1203	//	if creating file with name wich exist
ERR_CLOSE_CLOSED_F	1204	//	tryed closed file
ERR_FOLDER_FULL		1205	//	cannot write more files in this direct
ERR_NEED_FORMAT		1206	//	if need format file system
ERR_OPEN_NEXIST		1207	//	if tryed open not exist file


ERR_CANT_FINE_INODE 1208	//	if fail find inode of file by name
//	Be careful this error can be setted if you trying create file , becouse
//	check if the file with this name exist

ERR_INCORECT_FD		1209	//	when try used incorect file desc
ERR_INCORECT_INODE	1210	//	when try use incorect inode
ERR_ON_WRITE		1211	//	error on write
ERR_UNKNOWN_ON_WRITE 		1212	//	unknown error on write
ERR_UNKNOWN_ON_WRITE_BLOCK 	1213	//	ubknown error on write to block


ERR_ALL_FDT_FULL	1214	//	all fd-filetable is full
ERR_ALL_BLOCKS_FULL	1215	//	no free blocks-updated on search bitmap
ERR_ALL_INODES_FULL	1216	//	if all inodes used

For more errors codes see error.inc.h

//=============================================================================
	Unknown bugs
	There is no bugs
	
//=============================================================================
	Files Used
	
	# ex9.h		Header of filesystem
	# ex9.c		body off file system-functions

	# errors.inc.h		//	Errors include and code page
	# structures.inc.h	//	Structures used in program
	# defines.inc.h		//	All defines of program
	
	# main.c			//	Include main function
//=============================================================================
