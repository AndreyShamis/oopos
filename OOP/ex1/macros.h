#pragma once

#include <windows.h>
#include <vector>

//#include <GL/glut.h>
#include <glut.h>				//	TODO


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//	Color struct 
struct RgbColor
{
	float r;
	float g;
	float b;
};

enum{
	//	Menu options for drawing one shape from the avilables
	_DOT				=	11,
	_RECTANGLE			=	12,
	_SQUARE				=	13,
	_CIRCLE				=	14,
	_WHEEL				=	15,
	_EMPTY_CIRCLE		=	16,
	_H_LINE				=	17,
	_V_LINE				=	18,
	_ITRIANGLE			=	19,
	_EMPTY_RECTANGLE	=	20,
	_EQUIANGULAR		=	21,

	//	Main menu options see name 
	_CLEAR_SCREEN	=	122,
	_EXIT_PROGRAM	=	107,
	_PREV_SHAPE		=	101,
	_NEXT_SHAPE		=	102,
	_REMOVE_MARK	=	103,
	_UNDO			=	106,

	//	Colors options 
	_GREEN			=	0,
	_WHITE			=	1,
	_BLUE			=	2,
	_RED			=	3,
	_BLACK			=	4,
	_GRAY			=	5,

	//	Menu options for change
	//	and clear options
	_GROW_SELETED	=	201,
	_SHRINK_SELETED	=	202,
	_SAME_SIZE		=	203,
	_CLR_SELECTED	=	211,
	_CLR_SAME_TYPE	=	212,
	_CLR_SAME_COLOR	=	213,


	// UNDO	 options
	_UNDO_NOTHING	=	0,
	_UNDO_REMOVE	=	1,
	_UNDO_CHANGES	=	2,
	_UNDO_REMOVED	=	4,
	_UNDO_SELECT	=	3,

	//	COMMAND ON KEYBOARD
	_CMD_UNDO		=	26,
	_CMD_DELETE		=	127,
	_CMD_ESC		=	27,
	_CMD_GROW		=	43,
	_CMD_SHRINK		=	45,
	_CMD_SAME_SIZE	=	95,
	_CMD_PREV		=	90,
	_CMD_NEXT		=	88,
	_CMD_UNSELECT	=	32,
	_CMD_REMOVE_BY_TYPE	=	84,
	_CMD_REMOVE_BY_COLOR=	67,
	_CMD_REMOVE_ALL		=	65,

};