//
//  @ Project : Sentence Generator
//  @ File Name : mainp.cpp
//  @ Date : 06/05/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : main file of the program - that call function of the
//					managment of the program - menu and switch cases.

#pragma once

//============================= include section ===============================
//=============================================================================
#include "macros.h"
#include "SentenceGenerator.h"

//============================= prototype section =============================
//=============================================================================
// function which manage menu of the program
void manageProg();

//=============================================================================
// function which diplay menu to the std-out
void displayMenu();

//============================= main section ==================================
//=============================================================================
//=============================================================================
// main function
int main()
{
	manageProg();		// call function that manage the program

	return 0;

}

//=============================================================================
// function which manage menu of the program
void manageProg()
{
	char userChoise = 0;					// user choise	
	SentenceGenerator sGen;				// create object of Sentence Generator

	while(true)							// Loop till the user will want to exit
	{
		displayMenu();					// display menu on the std-out
		cin >> userChoise;				// get user choise

		switch(userChoise)				// switch user choise
		{

			case GEN_RUND_SENTENCE:		// Generate Random Sentence
				sGen.generateRandomSentence();
				break;
			case LOAD_FILE:				// Load Grammar File
				sGen.loadGrammarFile();
				break;
			case DISPLAY_RULES:			// DisplayGrammarFile
				sGen.displayGrammarFile();
				break;
			case EXIT:					// Exit program
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
	// Print the options
	cout	<< "Please Choose an option:\n" << "\n" 

			<< "1.  Generate a random sentence\n"
			<< "2.  Load a grammar file\n"
			<< "3.  Display grammar rules\n"
			<< "4.  Exit\n";

} 

