//
//  @ Project : Sentence Generator
//  @ File Name : SentenceGenerator.cpp
//  @ Date : 06/05/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : A class that is implimintation of Sentence Generator - do
//					all nesesery option of the requarments of the assitment:
//					do: generate random grammar sentence, load grammar file,
//						display the data base, chek corections and mach more.

#include "SentenceGenerator.h"


//=============================================================================
// constructor
SentenceGenerator::SentenceGenerator()
{
	 srand ((unsigned int)time(NULL));		// init randomation
	_dataBaseExist = false;					// the data base do not exist yet
}

//=============================================================================
// distractor
SentenceGenerator::~SentenceGenerator()
{
}

//=============================================================================
// function which load input grammar file to the STL data base. include cheking
// file gramar corection and file folts.
void SentenceGenerator::loadGrammarFile()
{
	if(!openFile(_gFile))			// if file dosen't opened - leave function
		return;

	bool fileIsGood = true;			// define file cuolety
	bool sentenceExist = false;		// define sentence existence
	string syntaxLaw;				// define syntax low
	string line;					// define line of file
	multimap<string,deque<string>> new_db;	// create new temp data base STL 

	while(_gFile.good())					// Loop til the end of file or folt
	{
		getline(_gFile,line);				// get line from file

		if(line.length() < 4)				// skip new-line and other garbeg 
			continue;

		deque<string> words = split(line);	// deque of wards from line

		if(words[0] == SENTENCE)			// search sentence-low existence
			sentenceExist = true;

		//chek if the first string is low and it is not the only string at line
		if((char)line[0] != '<' || (int)words.size() == 1)
			fileIsGood = false;

		syntaxLaw = words.front();			// exract the low from deque
		words.pop_front();					// delete the low from deque

		// insert the key low and the deque of words to the STL data base
		new_db.insert(pair<string,deque<string>>(syntaxLaw,words));
	}
	if(!chekLowExistence(new_db))			// chek if all the low exist
		fileIsGood = false;

	// if sentence low exist and cuolety of file is good:
	if(sentenceExist && fileIsGood)		
	{
		_db = new_db;						// update the main data base
		_dataBaseExist = true;				// data base now exist
		cout << "### Grammar file loaded successfully :) ###\n\n";
	}
	else									// stay with the old data base
		cout << "### Incomplete grammar or Wrong file format :( ###\n\n";

	_gFile.clear();				// clear the error flags of iostream.
	_gFile.close();				// close file	
	
}

//=============================================================================
// function which open file
// get file descriptor
// return true if open file, otherwise return false 
bool SentenceGenerator::openFile(ifstream &file)
{
	string fileName;				// define file name
	cout << "Please enter grammar file name that you want to load\n";

	cin >> fileName;				// get file name from user
	file.open(fileName.c_str());	// open file
	if(file.is_open())				// if file is open return true
		return true;

	cout << "### File does not exist ###\n\n";
	return false;					// file didn't opened - return false

}

//=============================================================================
// function which chek if some key (low) that located in the midel of the 
// sentence is exist at the keys at the STL container (first)
// get: the STL data base (by ref)
// return: false if the condition that discribe above not exist.
bool SentenceGenerator::chekLowExistence(multimap<string,deque<string>> &_db)
{
	// Loop  the container keys (first)
	for(multimap<string,deque<string>>::const_iterator itKey = _db.begin(); 
		itKey != _db.end(); ++itKey) 
	{
		// Loop  the container deques (second)
		for(deque<string>::const_iterator itSec = itKey->second.begin();
			itSec != itKey->second.end(); ++itSec)
		{
			bool keyExist = false;			// define key existence

			// if the word is low chek it at the keys
			if((char)(*itSec)[0] == '<')
			{
				// Loop  the container keys (first) to find low (key) existence
				for(multimap<string,deque<string>>::const_iterator itFirs = 
					_db.begin(); itFirs != _db.end(); ++itFirs) 
				{
					if(*itSec == (*itFirs).first)		// key exist
						keyExist = true;
				}
				if(!keyExist)							// key not exist
				
					return false;
			}
		}
	}
	return true;
}

//=============================================================================
// function which split sentence (string) to deque of words (strings)
// Get: sentence (string)
// return: deque of words (strings)
deque<string> SentenceGenerator::split(const string &sentence)
{
	deque<string> ret;						// deque of words (strings)
	istringstream iss(sentence);			//Construct an object and optionally 
											//initialize its content
	copy(istream_iterator<string>(iss),		// copy strings
		istream_iterator<string>(),			// iterator
		back_inserter<deque<string> >(ret));// split to deque
          
	return ret;
}

//=============================================================================
// function which 
void SentenceGenerator::displayGrammarFile()
{
	if(_dataBaseExist)
	{
		for (multimap<string,deque<string>>::const_iterator it = _db.begin(); 
			it != _db.end(); ++it) 
		{
			cout << it->first << "\t";
			printDeque(it->second);
			cout << "\n";
		}
		cout << "\n";
	}
	else
		printOperationCanceledMsg();

}

//=============================================================================
// function which 
void SentenceGenerator::printDeque(const deque<string> &deq)
{
	for (deque<string>::const_iterator it = deq.begin();
		it != deq.end(); ++it)
	
		cout << " " << *it;
}

//=============================================================================
// function which 
void SentenceGenerator::generateRandomSentence()
{
	if(_dataBaseExist)
	{
		cout << "Random generated sentence is:\n"; 
		generRandSenteRecur(SENTENCE);
		cout << "\n\n";
	}
	else
		printOperationCanceledMsg();
}


//=============================================================================
// function which 
void SentenceGenerator::generRandSenteRecur(const string &syntaxLaw)
{
	multimap<string,deque<string>>::iterator it;
	pair<multimap<string,deque<string>>::iterator,multimap<string,
	deque<string>>::iterator> ret;

	ret = _db.equal_range(syntaxLaw);

	int rnd = rand()%(int)_db.count(syntaxLaw);

	it = ret.first;

	for(int i = 0; i < rnd; i++) //  && it!=ret.second
	{
		++it;
	}
	for (deque<string>::const_iterator itr = (*it).second.begin();
		itr != (*it).second.end(); ++itr)
	{

		if((char)(*itr)[0] == '<')
			generRandSenteRecur(*itr);
		else
			cout << " " << *itr;
	}
}

//=============================================================================
// function which 
void SentenceGenerator::printOperationCanceledMsg()
{
	cout << "### OPERATION CANCELED ###";  
	cout << " - Yoy need to load a grammar file first!\n\n";
}