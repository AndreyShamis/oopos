//
//  @ Project : Sentence Generator
//  @ File Name : SentenceGenerator.h
//  @ Date : 06/05/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : A heder of class Sentence Generator

#pragma once

#include "macros.h"

class SentenceGenerator
{
public:
	SentenceGenerator();
	void generateRandomSentence();
	void loadGrammarFile();
	void displayGrammarFile();
	~SentenceGenerator();


private:
	void generRandSenteRecur(const string &syntaxLaw);
	void printOperationCanceledMsg();
	bool chekLowExistence(multimap<string,deque<string>> &_db);
	void printDeque(const deque<string> &deq);
	deque<string> split(const string &sentence);
	bool openFile(ifstream &file);
	multimap<string,deque<string>>	_db;			// the main data base (STL)
	ifstream						_gFile;			// file descriptor
	bool							_dataBaseExist;//define data base existence
};
