#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int MAX_INPUT_LEN 30;

void cycle();
void del_new_line(char *string);
int getstring(char *input,const int max_size);


int main()
{
	int example			;
	char example2='a'	;
	
    cycle();						

	puts("Bye-Bye");				

	return(EXIT_SUCCESS);			
}


void cycle()
{
	char 	input[MAX_INPUT_LEN];		
	FILE 	*pipe_fp;					

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

void del_new_line(char *string)
{
	int str_len	=	0;			

	str_len = strlen(string);	


	if(str_len > 1)		
		string[str_len-1] = '\0';

}

int getstring(char *input,const int max_size)
{
	if(fgets(input,max_size,stdin) != NULL)
	{
	
		del_new_line(input);
		return(1);
	}

	return(0);
}
