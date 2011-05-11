//
//  @ Project : Sentence Generator
//  @ File Name : mainp.cpp
//  @ Date : 06/05/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description :

#pragma once

#include "macros.h"
#include "SentenceGenerator.h"


using std::ifstream;
using std::ofstream;
//using std::setw;

using namespace std;




//=============================================================================
// function which manage menu of the program
void manageProg();

//=============================================================================
// function which diplay menu to the std-out
void displayMenu();






//=============================================================================
// main function
int main()
{
	manageProg();

	return 0;

}

//=============================================================================
// function which manage menu of the program
void manageProg()
{
	int userChoise = 0;
	SentenceGenerator sGen;

	while(true)
	{
		displayMenu();					// display menu on the std-out
		
		cin >> userChoise;				// get user choise

		switch(userChoise)
		{

			case GEN_RUND_SENTENCE:
				sGen.generateRandomSentence();
				break;
			case LOAD_FILE:
				sGen.loadGrammarFile();
				break;
			case DISPLAY_RULES:
				sGen.displayGrammarFile();
				break;
			case EXIT:
				cout << "bye bye!\n";
				return;
			default:
				cout << "### This option not supported ###\n\n";		
		}
	}
}
//=============================================================================
// function which diplay menu to the std-out
void displayMenu()
{
	cout	<< "Please Choose an option:\n" << "\n"

			<< "1.  Generate a random sentence\n"
			<< "2.  Load a grammar file\n"
			<< "3.  Display grammar rules\n"
			<< "4.  Exit\n";

} 
