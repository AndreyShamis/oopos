/*

	Provide server for clients which calculated pi
	and send it to server.
	Server waiting X second.X mast be provided in argv-2.


	also we add semaphore for safe comunication, when the server read from 
	the queue - the client is wating.
*/

//                               Include section
//=============================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>		// for using SHM
#include <sys/sem.h>		// for using SEM
#include <sys/ipc.h>
#include <sys/types.h>
#include <signal.h>			// for using signals
 

#define MAX_MSG_LEN 	13
#define XSI_IPC_FLAG	IPC_CREAT | IPC_EXCL | 0600
#define LOCK			-1
#define UNLOCK			1

//=============================================================================
//                        Variable and struct section

int quit = 0;	//global variable to get exit status can be updated in handler

//============================ STRUCTS ========================================
//	struct for retreidev messages
struct my_msgbuf
{
	long mtype;
	char mtext[MAX_MSG_LEN];
};

// struct for semaphor
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};


//	struct to save the list of nodes
struct Node
{
	struct my_msgbuf msgStorge;		//	struct my_msgbuf
	struct Node *_next;				//	Pointer to next Node in list
};
//=============================================================================
//								Prototypes
//=============================================================================
//	print message of incorrect input parameters
void incorect_param();

//=============================================================================
// A handler function
//	Updating gloabal to exit from program
void stopServer(int sig_num);

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	data geted by server in list
// Return:	value of PI
double calcAverage(struct Node *nod);

//=============================================================================
//	function which allocate new cell
//	return pointer to new cell
struct Node *Allocate_Node();

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg);

//=============================================================================
//	function wich clear the memory which was used
void clear_memory(struct Node *head);

//=============================================================================
//	function which print pi
void print_result(const double pai);

//=============================================================================
//	Function which retreive data and insert to list
//	Get the message queue_id
//	Return List
struct Node *retreive_data(const int queue_id, const int sem_set_id);

//=============================================================================
//	Function which manipulate whith list
//	For insert every new node to head of list and semaphore grupe id
//	Return manipulated list when pointer located on head of list
struct Node *getNextNode(struct Node *head);

//=============================================================================
//	Function which start msg
//	get ext-key definder and pointer to external key of msg queue
//  return msg queue id
int init_msg(const int ext_key, key_t *key);
//=============================================================================
//	Function which start semaphor
//	get pointer to external key of msg queue
//  return semaphore grup id
int init_sem(const key_t *key);

//=============================================================================
//	Function which close the msg system
void close_msg(const int queue_id);

//=============================================================================
//	Function which close the msg system
void close_sem(const int sem_set_id);

//=============================================================================
//	Function which set signal handler
void setHandlers();

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************


//=============================================================================
//	Main function
int main(int argc, char **argv)
{
	key_t 			key 		=	0;			//	ftok key
	int 			queue_id 	= 	0,			//	internal comunication key
					sem_set_id	=	0,			// 	semaphor grup id
	 				ext_key		=	0;			//	external comunication key
	struct Node 	*head 		= 	NULL;		//	DB of list
	double 			pai_res		=	0;			//	pi variable

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);						//	exit the program 
	}

	setHandlers();								//	set signal handlers

	ext_key 	= 	atoi(argv[1]);				//	get external key
	alarm(atoi(argv[2]));						//	set alarm

	queue_id 	= 	init_msg(ext_key,&key);		//	init msg
	sem_set_id	=	init_sem(&key);				//	init semaphor
	head 		= 	retreive_data(queue_id, sem_set_id);	//	retreive msg

	close_msg(queue_id);						//	close msg
	close_sem(sem_set_id);						//	close semaphore

	if(head!= NULL)
	{
		pai_res = 	calcAverage(head);			//	get value of pi
		print_result(pai_res);					//	print reults
		clear_memory(head);						//	clear memory used
	}
	return(EXIT_SUCCESS);

}

//=============================================================================
//	Function which set signal handler
void setHandlers()
{
	signal(SIGALRM, stopServer);		//	set signal handler for Alarm
	signal(SIGINT, stopServer);			//	set signal handler for sigInt

}

//=============================================================================
//	Function which start msg
//	get ext-key definder and pointer to external key of msg queue
//  return msg queue id
int init_msg(const int ext_key, key_t *key)
{
	int 			queue_id	= 0;	// msg desc id

	if(((*key) = ftok("/tmp", ext_key)) == -1)			// creat external key
		errExit("ftok()failed\n");		// Print error and exit

	if((queue_id = msgget((*key),XSI_IPC_FLAG)) == -1)	// init msg
		errExit("msgget()failed\n");	// Print error and exit

	return(queue_id);					// return msg desc id

}

//=============================================================================
//	Function which start semaphor
//	get pointer to external key of msg queue
//  return semaphore grup id
int init_sem(const key_t *key)
{
	int		sem_set_id	= 0;								// semaphor grup id
	union 	semun sem_val;
			
	if((sem_set_id = semget((*key),1,XSI_IPC_FLAG))== -1)	// creat semaphore
		errExit("semget()failed\n");		// Print error and exit

	sem_val.val = 1;						// init value of semaphor

	if(semctl(sem_set_id,0,SETVAL,sem_val) == -1)			// init semaphore
		errExit("semctl()failed\n");		// Print error and exit

	return(sem_set_id);						// return sem grup id

}

//=============================================================================
//	Function which retreive data and insert to list
//	Get the message queue_id and semaphore grupe id
//	Return List
struct Node *retreive_data(const int queue_id, const int sem_set_id)
{
			
	struct sembuf 		sem_op;	// structure for semaphor operations
	struct my_msgbuf 	my_msg;	// difine transfer data structur.
	int 				status;	// difine volume of retreive data or failiar.

	// allowed type of information to be retreive from clients
	// (allowed type of key). equal to 0 because server get any type of data.
	long int 			allowed_type 	= 	0;

	struct Node 		*head 			= 	NULL;// Db linked list

	while(!quit)  // loop till the and of timer (argv[2]) or till "Ctrl^c"
	{
		// Entry section:

		// wait on the semaphore unless it's value is non-negative.
		sem_op.sem_num	=	0;					// num of sem in set
		sem_op.sem_op	=	LOCK;				// wait operation
		sem_op.sem_flg	=	0;					// flags we leave 0
		if(semop(sem_set_id, &sem_op, 1) == -1)
			errExit("semop()failed\n");			// Print error and exit

		// The Critical Section:
		status = msgrcv(queue_id,(struct msgbuf*)&my_msg,		// reciv msg
						MAX_MSG_LEN, allowed_type, IPC_NOWAIT);
		if(status > 0)
		{
			head= getNextNode(head);			//	manipulation with list
			head->msgStorge = my_msg;			//	copy data recived
		}

		sleep(1);								//	sleep

		// Exit Section:

		// finally, signal the semaphore - increase it's value by one.
		sem_op.sem_num	=	0;					// num of sem in set
		sem_op.sem_op	=	UNLOCK;				// signal operation 
		sem_op.sem_flg	=	0;					// flags we leave 0
		if(semop(sem_set_id, &sem_op, 1) == -1) // activate semaphore operation
			errExit("semop()failed\n");			// Print error and exit
	}

	return(head); // return head of link list which contain msg's from clients

}

//=============================================================================
//	Function which manipulate whith list
//	For insert every new node to head of list
//	Return manipulated list when pointer located on head of list
struct Node *getNextNode(struct Node *head)
{
	struct Node *temp 	= 	NULL;		//	temporary variable

	if(head == NULL)					//	if list empty yet
		head = Allocate_Node();			//	create new node
	else
	{									//	if list not empty
		temp = Allocate_Node();			//	crerate new node
		temp->_next = head;				//	new node point to head of list
		head = temp;					//	new node be head of list
	}

	return(head);						//	return head of list

}

//=============================================================================
//	function which print pi
//	get value of pai
void print_result(const double pai)
{
	fprintf(stdout,"pai = %.10f\n", pai);	//	print to stdout - pai result

}

//=============================================================================
//	function which allocate new cell
//	return pointer to new cell
struct Node *Allocate_Node()
{
	struct Node *temp = NULL;					//	temp variable

	temp = malloc(sizeof(struct Node));			//	allocate new node

	if(temp == NULL)	//	if not success allocate new node
		errExit("Can not allocate memory.\n");	//	print err message

	temp->_next = NULL;	//	set pointer to next be NULL

	return(temp);								//	return new node

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg)
{
	perror(msg);					//	print err message
	exit(EXIT_FAILURE);				//	exit whith fail
}

//=============================================================================
//	function wich clear the memory which was used for linked list.
//	get pointer to the head of list
void clear_memory(struct Node *head)
{
	struct Node *temp = NULL;		//	temp variable

	while(head != NULL)				//	while the node is not null
	{
		temp = head->_next;			//	set temp be next
		free(head);					//	delete this
		head= temp;					//	next be this
	}

}

//=============================================================================
//	Function ti calculate Pi over all clients was geted
// Inpu-t:	data geted by server in list
// Return:	value of PI
double calcAverage(struct Node *nod)
{
	double 		average 	= 	0;		//	difine average of retreive pais.
	long int 	divides 	= 	0;		//	difine weight of calculation averag
	struct Node *temp 		= 	NULL;	//	temp variable

	temp = nod;							//	get head of list

	while(temp!=NULL)	// calculation of average.
	{
		average += temp->msgStorge.mtype * atof(temp->msgStorge.mtext);
		divides += temp->msgStorge.mtype;
		temp = temp->_next;				//	get next node in list
	}

	if(divides)							//	check if can devide
	{
		average = average / divides;	//	deviding
		return (average);				//	return value
	}

	return (0);							//	return other value

}

//=============================================================================
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. queue_id\n");
	printf("2. time for timer\n");

}

//=============================================================================
//	Function which close the msg system
void close_msg(const int queue_id)
{
	if(msgctl(queue_id, IPC_RMID, NULL) == -1)		// close msg file
		errExit("msgctl()failed\n");				// print error and exit

}

//=============================================================================
//	Function which close the msg system
void close_sem(const int sem_set_id)
{
	if(semctl(sem_set_id,0 , IPC_RMID, NULL) == -1)		// close semaphore grup
		errExit("emctl()failed\n");						// print error and exit

}

//=============================================================================
// A handler function
//	Updating gloabal to exit from program 
void stopServer(int sig_num)
{
	quit = 1;							//	exit status from program

}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

