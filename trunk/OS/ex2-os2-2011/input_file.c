#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>

#define MAX_SIZE  255


int global_variable=0;
char ch;

char charer[10];
char piska='2';

bool GetParameters(ifstream &tfi, char pattern[],char text[],int &start_postion,int &mismatch);
void WriteToFile(ofstream &tfo, int data);


int main(int argc, char* argv[])
{
    char    pattern[MAX_SIZE];     
    int     from_pos        = 0;   
    int     ret= 0; 
	ifstream tfi;                  
    ofstream tfo;           
	
	cout << "lolfor check //";
    tfi.open(argv[1]);                 
    tfo.open(argv[2], ofstream::out);  

    if(tfi.is_open() && tfo.is_open())
        while(!tfi.eof())
            if(GetParameters(tfi,pattern,text,from_pos,mismatch))
            {
          
                ret = inexact_pos(pattern,text,from_pos,mismatch);

                if(ret<0)
                    no_counter++;      

                row_counter++;         

                WriteToFile(tfo,ret);   

            }

    tfi.close();    
    tfo.close();    

    cout << row_counter << " " << no_counter << "\n";

    return(EXIT_SUCCESS);  
}


void WriteToFile(ofstream &tfo, int data)
{
	int not_used_variable;
	
    tfo << data << "\n";    

}

bool GetParameters(ifstream &tfi, char pattern[],char text[],int &start_postion,int &mismatch)
{

	const char werd='d';
    char    pattern[MAX_SIZE];     
    int     from_pos        = 0;   
    int     ret= 0; 
	ifstream tfi;                  
    ofstream tfo;     	
        tfi >> setw(MAX_SIZE) >> pattern; 
        tfi >> setw(MAX_SIZE) >> text;      
        tfi >> start_postion;              
        tfi >> mismatch;                   

        if(!tfi.fail())        
           return(true);       
        else
           return (false);     
}
