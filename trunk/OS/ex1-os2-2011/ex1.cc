/*
 * EX1a  :: Making file parsing and distribution components
 * ============================================================================
 * Writen by: Andrey Shamis, id: 321470882 login:andreysh
 			  Ilia Gaisinsky,  id: 309480051, login: iliaga
 *
 * This program is called input data file.
 * The program will receive through Name of a file which will serve as an
 * input of the program. This file reading program the data. Beyond that the
 * program will receive through her other arguments names
 * Three output files:
 *  Output file to send strings of letters that the plan call (input file)
 *  (argv [2])
 *  (argv [3]) 2. Output file to be sent to the numbers (all types) plan call
 *  (Argv [4]) 3. Output file to send junk strings
 *
 *  to compile use: g++ -Wall ex1a.cc -o ex1a
 */

//--------------- including section -------------------------------------------
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <cstring>

//--------------- using section        ----------------------------------------
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;


#define FIRST_IN 1
#define SECOND_IN 2
#define THIRD_IN 3
#define FOURT_IN 4
#define CH_NEW_LINE '\n'
#define CH_PLUS '+'
#define CH_MINUS '-'
#define CH_DOT '.'
#define CH_SPACE ' '
#define NUM_FILES_NEEDED 4
//-------------- const & enum section -----------------------------------------
enum char_state{            // group of types
        num     =   2,      // numbers/digits
        alpha   =   1,      // alpha
        junk    =   3,      // other
};
const int MAX_FILES_OUTPUT = 3; // var for set how meny files be writes


//--------------  Prototypes section ------------------------------------------

//------------------------- GET TYPE OF CHAR GROUP ----------------------------
//  Function that distributes all the characters into three groups
//  letters
//  figures
//  rest
//  And returns the type of group
int GetType(const char ch);
//----------------------------------------------------------------------------
//	Check if number parameters is correct
void checkCorrectInput(const int &val);
//---------------------------- WRITE TO FILE ----------------------------------
// function writing into file <file_name> the data
void WriteToFile(ofstream &tfo, char data);

//--------------------------- PREWRITE ----------------------------------------
// Automatic file selection for writing.
// Just write char which has a file that is received.
void PreWrite(int state,ofstream &tf_alf,ofstream &tf_num,
    ofstream &tf_nul,const char real_ch);

//----------------------- OPEN OUT PUT FILE -----------------------------------
// The function opens the specified file for writing.
// Object to open the file is returned in the  reference variable
bool OpenOutPut(ofstream &file_obj,const char file_name[]);

//--------------------------- GET CHARS ---------------------------------------
// Function manipulation with the chars, the next char, this char as well
// as the previous one char.If unable to take the sign returns false,
// if taken back the truth, and in alternating directions
// and communicates information
bool GetChars(ifstream &in_obj, char &prev_ch,char &real_ch,char &next_ch);

//-------------------------- COUNTLAST ----------------------------------------
// Counter lines. Works with an array.
// 0 - alpha;1-numbers;2-junk
void countLast(int counter_db[], int counter_id);

//--------------------------- GURB2NUM ----------------------------------------
// function that determines the point and plus and minus signs,
// and if it finds those that might be appropriate
//  to the numbers returns true, otherwise false
bool Garb2Num(char r_ch,int n_state,int p_state, bool &dot,bool &plus_minus);


//--------------- main                 ----------------------------------------
int main(int argc, char* argv[])
{

    int         res_count[MAX_FILES_OUTPUT];    // counter for all types
    int         state       =   0,              // variables for chars type
                prv_st      =   0,              // every char have self type
                next_state  =   0;              // 1-alpha;2-digits;3-other
    char        real_ch,    prev_ch,    next_ch;    // variables to chars
    bool        have_dot           = false,     // variables to work with ./+/-
                plus_minus         = false;     // which can be digit
    bool        new_line           = false;     // var for set if find '\n'
	ifstream    tfi;                        // prototype for reading files
    ofstream    tf_num , tf_alf , tf_nul;   // prototypes for writing files
	checkCorrectInput(argc);				//	check param
    // open file for reading
    tfi.open(argv[FIRST_IN]);
    // Set string counters to zero position
    memset(res_count,0,sizeof(res_count));
    // here check if read file is opened and if writig files opened
    if(tfi.is_open() && OpenOutPut(tf_alf,argv[SECOND_IN])
    && OpenOutPut(tf_num,argv[THIRD_IN]) && OpenOutPut(tf_nul,argv[FOURT_IN]))
    {	// check if get char success doing while
        while(GetChars(tfi,prev_ch,real_ch,next_ch))
        {
            if(real_ch == CH_NEW_LINE)
            {
                new_line    = true;
                WriteToFile(tf_num,real_ch);    // write \n to numbers
                WriteToFile(tf_alf,real_ch);    // write \n to alpha
                WriteToFile(tf_nul,real_ch);    // write \n to junk
                countLast(res_count,prv_st);    // add counter to last type
                continue;
            }
            state       =   GetType(real_ch);   // get type of curent char
            next_state  =   GetType(next_ch);   // get type of next chare
            // section to check "./+/-" for number
            if(Garb2Num(real_ch,next_state,prv_st,have_dot,plus_minus))
                state           = num;

            // start block which working whith spaces
            if((prev_ch == CH_SPACE && prev_ch == real_ch))
                ;   // have to much spaces do nothing
            else if((state != prv_st  && prev_ch != CH_SPACE && !new_line)
                || (prv_st == num && (real_ch==CH_MINUS || real_ch==CH_PLUS))
                || (prv_st == state && state == junk && real_ch == CH_SPACE))
            {   // write space to last file because start work with
                // enother type of chars
                PreWrite(prv_st, tf_alf,tf_num,tf_nul,CH_SPACE);// write space
                countLast(res_count,prv_st);                // add counter
            }

            if(real_ch != CH_SPACE)              // block which writing into
                PreWrite(state, tf_alf,tf_num,tf_nul,real_ch);

            // check if next char is not good for a number
            // if not set bools to next number use
            if(next_state != num && next_ch != CH_DOT)
            {
                have_dot    = false;
                plus_minus  = false;
            }
            prv_st      = state;        // transit real state to prev state
            new_line    = false;        // set bool new line be false
        }
        // print counters data to std::out
        cout    << res_count[alpha-1]   << " " << res_count[num-1]     << " "
                << res_count[junk-1]    << "\n";
    }
    else
    {
        cerr << "Error opening input file!" << endl;    // return error
        return(EXIT_FAILURE);
    }

    tfi.close();        // close reasd file
    tf_num.close();     // close numbers file
    tf_alf.close();     // close alpha file
    tf_nul.close();     // close junk file

    return(EXIT_SUCCESS);   // exit from the program

}

//----------------------------------------------------------------------------
//	Check if number parameters is correct
void checkCorrectInput(const int &val)
{
	if(val != NUM_FILES_NEEDED+1)
	{
        cerr << "Need set 4 path to files" << endl;    // return error
        exit(EXIT_FAILURE);
	}
}
//--------------------------- GURB2NUM ----------------------------------------
// function that determines the point and plus and minus signs,
// and if it finds those that might be appropriate
//  to the numbers returns true, otherwise false
bool Garb2Num(char r_ch,int n_state,int p_state, bool &dot,bool &plus_minus)
{

    if(p_state == num && r_ch == '.' && n_state == num  && !dot)
    {   // do it find dot for number
        dot        = true;  // set boolean var be true only if have "."
        return(true);
    }
    else if((r_ch==CH_MINUS || r_ch==CH_PLUS) && n_state==num && !plus_minus)
    {   // do it if find - or + for numer
        plus_minus = true;  // set boolean var be true only if have "+/-"
        return(true);
    }

    // if not finded have return false

    return(false);

}

//-------------------------- COUNTLAST ----------------------------------------
// Counter lines. Works with an array.
// 0 - alpha;1-numbers;2-junk
void countLast(int counter_db[], int counter_id)
{
    counter_id--;               // must be counter_id - 1
    counter_db[counter_id]++;   // add 1 to counter

}

//--------------------------- GET CHARS ---------------------------------------
// Function manipulation with the chars, the next char, this char as well
// as the previous one char.If unable to take the sign returns false,
// if taken back the truth, and in alternating directions
// and communicates information
bool GetChars(ifstream &in_obj, char &prev_ch,char &real_ch,char &next_ch)
{

        prev_ch = real_ch;      // transit real char to be previw char

        real_ch = in_obj.get(); // geting next char

        if(in_obj.fail() || in_obj.eof())  // check if get file success
            return (false);     // if not return false
        else
            next_ch = in_obj.peek(); // geting *next char

        return(true);

}

//--------------------------- PREWRITE ----------------------------------------
// Automatic file selection for writing.
// Just write char which has a file that is received.
void PreWrite(int state,ofstream &tf_alf,ofstream &tf_num,
    ofstream &tf_nul,const char real_ch)
{
    switch(state)
    {
        case 1:
            WriteToFile(tf_alf,real_ch);    // write char to alpha file
            break;
        case 2:
            WriteToFile(tf_num,real_ch);    // write char to numbers file
            break;
        case 3:
            WriteToFile(tf_nul,real_ch);    // write file to junk file
            break;
    }

}

//----------------------- OPEN OUT PUT FILE -----------------------------------
// The function opens the specified file for writing.
// Object to open the file is returned in the  reference variable
bool OpenOutPut(ofstream &file_obj,const char file_name[])
{


    file_obj.open(file_name, ofstream::out);    // open file for writing

    if(file_obj.is_open())  // check if open func success
        return (true);      // if yes return T
    else
        return (false);     // if not open

}

//---------------------------- WRITE TO FILE ----------------------------------
// function writing into file <file_name> the data
void WriteToFile(ofstream &tfo, char data)
{
    tfo << data;            // function which writing into file
}

//------------------------- GET TYPE OF CHAR GROUP ----------------------------
//  Function that distributes all the characters into three groups
//  letters
//  figures
//  rest
//  And returns the type of group
int GetType(const char ch)
{
    int state = 0;

    if(isdigit(ch))         // check if this char it is number 0-9
        state = num;
    else if(isalpha(ch))    // check if this char is alpha [A-Za-z]
        state = alpha;
    else                    // !alpha && !numbers(digits)
        state = junk;

    return(state);

}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
