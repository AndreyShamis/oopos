//
//  @ Project : Sentence Generator
//  @ File Name : macros.h
//  @ Date : 06/05/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : maintanace\configuration file.

#pragma once


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <map>
#include <time.h>

using namespace std;
using std::ifstream;

// Menu options
#define GEN_RUND_SENTENCE	'1'
#define LOAD_FILE			'2'
#define DISPLAY_RULES		'3'
#define EXIT				'4'


#define SENTENCE "<sentence>"
#define INF_REC_LIMIT		5 // limit of infinity recurtion