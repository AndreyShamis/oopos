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
	int userChoise = 0;					// user choise	
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















//
////
////  @ Project : Sentence Generator
////  @ File Name : SentenceGenerator.cpp
////  @ Date : 06/05/2011
////  @ Authors : Ilia Gaysinski and Andrey Shamis
////	@ Description :
//
//#include "SentenceGenerator.h"
//
//
////=============================================================================
//// constructor
//SentenceGenerator::SentenceGenerator()
//{
//	srand ( time(NULL) );
//	_dataBaseExist = false;
//}
//
//SentenceGenerator::~SentenceGenerator()
//{
//}
//
////=============================================================================
//// function which 
//void SentenceGenerator::loadGrammarFile()
//{
//	if(!openFile(_gFile))
//		return;
//
//	bool fileIsGood = true;
//	bool sentenceExist = false;
//	string syntaxLaw;
//	string line;
//	multimap<string,deque<string>> new_db;
//
//	while(_gFile.good())
//	{
//		getline(_gFile,line);
//
//		deque<string> words = split(line);
//
//		if(words[0] == SENTENCE)
//			sentenceExist = true;
//
//		if((char)line[0] != '<' || (int)words.size() == 1)
//			fileIsGood = false;
//
//		syntaxLaw = words.front();
//		words.pop_front();
//		new_db.insert(pair<string,deque<string>>(syntaxLaw,words));
//	}
//	fileIsGood = chekLowExistence(new_db);
//	if(sentenceExist && fileIsGood)
//	{
//		_db = new_db;
//		_dataBaseExist = true;
//		cout << "### Grammar file loaded successfully :) ###\n\n";
//	}
//	else
//		cout << "### Incomplete grammar or Wrong file format :( ###\n\n";
//
//	_gFile.close();
//
//}
//
////=============================================================================
//// function which 
//bool SentenceGenerator::openFile(ifstream &file)
//{
//	string fileName;
//	cout << "Please enter grammar file name to that you want to load\n";
//
//	cin >> fileName;
//	file.open(fileName.c_str());
//	if(file.is_open())
//		return true;
//
//	cout << "### File does not exist ###\n\n";
//	return false;	
//
//}
//
////=============================================================================
//// function which 
//bool SentenceGenerator::chekLowExistence(multimap<string,deque<string>> &_db)
//{
//	for(multimap<string,deque<string>>::const_iterator itKey = _db.begin(); 
//		itKey != _db.end(); ++itKey) 
//	{
//		for(deque<string>::const_iterator itSec = itKey->second.begin();
//			itSec != itKey->second.end(); ++itSec)
//		{
//			bool keyExist = false;
//			if((char)(*itSec)[0] == '<')
//			{
//				for(multimap<string,deque<string>>::const_iterator itFirs = 
//					_db.begin(); itFirs != _db.end(); ++itFirs) 
//				{
//					if(*itSec == (*itFirs).first)
//						keyExist = true;
//				}
//				if(!keyExist)
//					return false;
//			}
//		}
//	}
//	return true;
//}
//
////=============================================================================
//// function which 
//deque<string> SentenceGenerator::split(const string &sentence)
//{
//	deque<string> ret;
//	istringstream iss(sentence);
//	copy(istream_iterator<string>(iss),
//		istream_iterator<string>(),
//		back_inserter<deque<string> >(ret));
//          
//	return ret;
//}
//
////=============================================================================
//// function which 
//void SentenceGenerator::displayGrammarFile()
//{
//	if(_dataBaseExist)
//	{
//		for (multimap<string,deque<string>>::const_iterator it = _db.begin(); 
//			it != _db.end(); ++it) 
//		{
//			cout << it->first << "\t";
//			printDeque(it->second);
//			cout << "\n";
//		}
//		cout << "\n";
//	}
//	else
//		printOperationCanceledMsg();
//
//}
//
////=============================================================================
//// function which 
//void SentenceGenerator::printDeque(const deque<string> &deq)
//{
//	for (deque<string>::const_iterator it = deq.begin();
//		it != deq.end(); ++it)
//	
//		cout << " " << *it;
//}
//
////=============================================================================
//// function which 
//void SentenceGenerator::generateRandomSentence()
//{
//	if(_dataBaseExist)
//	{
//		cout << "Random generated sentence is:\n"; 
//		generRandSenteRecur(SENTENCE);
//		cout << "\n\n";
//	}
//	else
//		printOperationCanceledMsg();
//}
//
//
////=============================================================================
//// function which 
//void SentenceGenerator::generRandSenteRecur(const string &syntaxLaw)
//{
//	multimap<string,deque<string>>::iterator it;
//	pair<multimap<string,deque<string>>::iterator,multimap<string,
//	deque<string>>::iterator> ret;
//
//	ret = _db.equal_range(syntaxLaw);
//
//	int rnd = rand()%(int)_db.count(syntaxLaw);;
//
//	it = ret.first;
//
//	for(int i = 0; i < rnd; i++) //  && it!=ret.second
//	{
//		++it;
//	}
//	for (deque<string>::const_iterator itr = (*it).second.begin();
//		itr != (*it).second.end(); ++itr)
//	{
//
//		if((char)(*itr)[0] == '<')
//			generRandSenteRecur(*itr);
//		else
//			cout << " " << *itr;
//	}
//}
//
////=============================================================================
//// function which 
//void SentenceGenerator::printOperationCanceledMsg()
//{
//	cout << "### OPERATION CANCELED ###";  
//	cout << " - Yoy need to load a grammar file first!\n\n";
//}