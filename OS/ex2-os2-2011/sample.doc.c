#include <stdlib.h>	/* include stdlib */
#include <string.h>	/* include string function */
#include <unistd.h>	/* for pipe */
#include <stdio.h>	/* standart */
#include <errno.h>	/* for error */

int MAX_INPUT_LEN 30;	/* used for max string len can be entered */

/* main cycle function */
void cycle();
/* function for deleting char new line */
void del_new_line(char *string);
/* function for get string  */
int getstring(char *input,const int max_size);


int main()
{
	int example			;	/* dis not used variable.only for example */
	char example2='a'	;	/* also not used */

    /* call to cycle function */
	
    cycle();						

    /* print bye */
	puts("Bye-Bye");				

    /* exit from program */
	return(EXIT_SUCCESS);			


}


/* 
 * The function get:
 *
 * The function return:
 * 	The function not return ant thing 
 *
 * function performs the following steps:
 * 	This is main cycle function which ask for user what to do 
 */
void cycle()
{
	char 	input[MAX_INPUT_LEN];			/* This is for input variable */
	FILE 	*pipe_fp;						/* Pointer to pipe */

	while(getstring(input,MAX_INPUT_LEN))
	{

		if(!strcmp(input,"exit"))		
			break;
		else if(!strcmp(input,"\n"))	
			continue;

		if((pipe_fp = popen(input,"w")) == NULL)
		{
			perror("popen _error");	
			exit(EXIT_FAILURE);			
		}
		else
			pclose(pipe_fp);
			
	}
}

/* 
 * The function get:
 *	char *string 	-  The string when need delete new line
 *
 * The function return:
 * 	Nothing be returned 
 *
 * function performs the following steps:
 * 	Deliting the new line symbol from string 
 */
void del_new_line(char *string)
{
	int str_len	=	0;				/* Variable for check what is the string len */

	str_len = strlen(string);	


	if(str_len > 1)		
		string[str_len-1] = '\0';

}

/* 
 * The function get:
 *	char *input 	-  Pointer when be located input
 *	const int max_size 	-  The max size be located in the input string
 *
 * The function return:
 * 	The function return 1 - if success 0 - failed get input 
 *
 * function performs the following steps:
 * 	Geting input from user and put it to pointer. 
 */
int getstring(char *input,const int max_size)
{
	if(fgets(input,max_size,stdin) != NULL)
	{
	
		del_new_line(input);
		return(1);
	}

	return(0);
}
