#define MAX_ERRORS			10		//	number of last errors saved in fs_struc

#define ERR_FILE_FULL 		1200	//	if tryed read/write more than can
#define ERR_READ_CLOSED		1201	//	if read closed file
#define ERR_WRITE_CLOSED	1202	//	if tryed write closed file
#define ERR_FILE_EXIST		1203	//	if creating file with name wich exist
#define ERR_CLOSE_CLOSED_F	1204	//	tryed closed file
#define ERR_FOLDER_FULL		1205	//	cannot write more files in this direct
#define ERR_NEED_FORMAT		1206	//	if need format file system
#define ERR_OPEN_NEXIST		1207	//	if tryed open not exist file


//#define ERR_			120
