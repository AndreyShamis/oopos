#define MAX_ERRORS			40		//	number of last errors saved in fs_struc

#define ERR_FILE_FULL 		1200	//	if tryed read/write more than can
#define ERR_READ_CLOSED		1201	//	if read closed file
#define ERR_WRITE_CLOSED	1202	//	if tryed write closed file
#define ERR_FILE_EXIST		1203	//	if creating file with name wich exist
#define ERR_CLOSE_CLOSED_F	1204	//	tryed closed file
#define ERR_FOLDER_FULL		1205	//	cannot write more files in this direct
#define ERR_NEED_FORMAT		1206	//	if need format file system
#define ERR_OPEN_NEXIST		1207	//	if tryed open not exist file


#define ERR_CANT_FINE_INODE 1208	//	if fail find inode of file by name
//	Be careful this error can be setted if you truing create file , becouse
//	check if the file with this name exist

#define ERR_INCORECT_FD		1209	//	when try used incorect file desc
#define ERR_INCORECT_INODE	1210	//	when try use incorect inode
#define ERR_ON_WRITE		1211	//	error on write
#define ERR_UNKNOWN_ON_WRITE 		1212	//	unknown error on write
#define ERR_UNKNOWN_ON_WRITE_BLOCK 	1213	//	ubknown error on write to block


#define ERR_ALL_FDT_FULL	1214	//	all fd-filetable is full
#define ERR_ALL_BLOCKS_FULL	1215	//	no free blocks-updated on search bitmap
#define ERR_ALL_INODES_FULL	1216	//	if all inodes used
//#define ERR_			120
