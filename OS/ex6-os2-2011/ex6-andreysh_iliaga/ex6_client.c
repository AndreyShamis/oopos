/*
	This file are client which connected to server and send him
	the pi value are is calculeted in function culcPai by MonteCarlo method.

	also we add semaphore for safe comunication, when the client wright to 
	the queue - the server is wating.

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
#include <time.h>
#include <math.h>


#define PERMISSION		0600
#define MAX_MSG_LEN 	13
#define LOCK			-1
#define UNLOCK			1
#define MULTPL			1000
#define FOUR_DEF		4

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

//                             Prototypes section
//=============================================================================

//=============================================================================
//	print message of incorrect input parameters
void incorect_param();
//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg);

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
//	function to calculate Pi
//	geting multiplayer
//	return claculated value
double culcPai(int multiplier);

///////////////////////////////////////////////////////////////////////////////
//                                Main section
//=============================================================================
int main(int argc, char **argv)
{
	key_t 				key 			=	0;	// ftok key
	int 				queue_id		=	0,	// internal comunication key
						sem_set_id		=	0;	// semaphor grup id
	double				pai_calculated	=	0;  // pai value.
	struct my_msgbuf 	my_msg;					// transfer data structur.
	struct sembuf 		sem_op;	// structure for semaphor operations

	// If the user enter nesesery data corect:
	if(argc != 3)
	{
		incorect_param();						//	print error
		exit(EXIT_FAILURE);						//	exit the program 
	}

	queue_id 		= 	init_msg(atoi(argv[1]), &key);	//	init msg
	sem_set_id		=	init_sem(&key);					//	init semaphor

	my_msg.mtype 	= 	atoi(argv[2]);			// put second param to msg type
	memset(my_msg.mtext,'\0',sizeof(my_msg.mtext));	// to be shur that clin str
	pai_calculated 	=	culcPai(atoi(argv[2]));		// calc pai.
	sprintf(my_msg.mtext, "%.10f\n",pai_calculated);// Print pai.

	// #### Entry section:

	// wait on the semaphore unless it's value is non-negative
	sem_op.sem_num	=	0;					// num of sem in set
	sem_op.sem_op	=	LOCK;				// wait operation
	sem_op.sem_flg	=	0;					// flags we leave 0
	if(semop(sem_set_id, &sem_op, 1) == -1)
		errExit("semop()failed\n");			// Print error and exit


	// ### The Critical Section:
	// Send messeg to server.																
	if(msgsnd(queue_id, (struct msgbuf*)&my_msg, MAX_MSG_LEN, IPC_NOWAIT))
		errExit("msgsnd()failed\n");

	// ### Exit Section:

	// finally, signal the semaphore - increase it's value by one.
	sem_op.sem_num	=	0;					// num of sem in set
	sem_op.sem_op	=	UNLOCK;				// signal operation 
	sem_op.sem_flg	=	0;					// flags we leave 0
	if(semop(sem_set_id, &sem_op, 1) == -1)
		errExit("semop()failed\n");			// Print error and exit

	return(EXIT_SUCCESS);

}


//                             Function section
//=============================================================================


//=============================================================================
//	Function which start msg
//	get ext-key definder and pointer to external key of msg queue
//  return msg queue id
int init_msg(const int ext_key, key_t *key)
{
	int 			queue_id	= 0;	// msg desc id

	if(((*key) = ftok("/tmp", ext_key)) == -1)		// connect to exist key
		errExit("ftok()failed\n");		//			Print error and exit

	if((queue_id = msgget((*key),0)) == -1)			// init msg
		errExit("msgget()failed\n");	// Print error and exit

	return(queue_id);					// return msg desc id

}

//=============================================================================
//	Function which start semaphor
//	get pointer to external key of msg queue
//  return semaphore grup id
int init_sem(const key_t *key)
{
	int		sem_set_id	= 0;				// semaphor grup id

	if((sem_set_id = semget((*key),1,PERMISSION))== -1)		// creat semaphore
		errExit("semget()failed\n");		// Print error and exit

	return(sem_set_id);						// return sem grup id

}

//=============================================================================
//	function which print error which get in parameter
//	and exit from the programm
void errExit(char *msg)
{
	perror(msg);						//	Print message
	exit(EXIT_FAILURE);					//	exit whith failure
}

//=============================================================================
//	print message of incorrect input parameters
void incorect_param()
{
	printf("You need enter 2 parameters:\n");
	printf("1. queue_id\n");
	printf("2. multiplier for rand\n");

}

//=============================================================================
//	function to calculate Pi
//	geting multiplayer (argv[2])
//	return claculated value
double culcPai(int multiplier)
{

	double xVal,		// rndom x coordinate value.
		   yVal,		// rndom y coordinate value.
		   distance,	// distance of points.
		   totalPoints = multiplier * MULTPL,// difine total points number.
		   pointsIn = 0;

	int index;	// for Looping.

	srand(time(NULL));	// init random.

	// Loop thrugh all random points, and calculate num of point in the circel.
	for(index = 0; index < totalPoints; index ++)
	{
		xVal = (double) rand()/RAND_MAX;
		yVal = (double) rand()/RAND_MAX;

		// alculate num of point in the circel
		distance = (xVal * xVal) + (yVal * yVal);
		distance = distance * distance;

		if(distance <= 1)
			pointsIn ++;

	}
	// return pai propabilety value.
	return (FOUR_DEF * (pointsIn / totalPoints));
}

//=============================================================================
//=============================================================================
//=============================================================================
