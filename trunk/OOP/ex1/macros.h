#pragma once

#include <windows.h>
#include <vector>

//#include <GL/glut.h>
#include <glut.h>


#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

struct RgbColor
{
	float r;
	float g;
	float b;
};

enum{
	_DOT		=	11,
	_RECTANGLE	=	12,
	_SQUARE		=	13,
	_CIRCLE		=	14,
	_WHEEL		=	15,
	_CIRCLE_HOLE=	16,
	_H_LINE		=	17,
	_V_LINE		=	18,
	_TRIANGLE	=	19,

	_CLEAR_SCREEN	=	122,
	_EXIT_PROGRAM	=	107,
	_PREV_SHAPE		=	101,
	_NEXT_SHAPE		=	102,
	_REMOVE_MARK	=	103,

	_GREEN			=	0,
	_WHITE			=	1,
	_BLUE			=	2,
	_RED			=	3,
	_BLACK			=	4,


	_GROW_SELETED	=	201,
	_SHRINK_SELETED	=	202,
	_SAME_SIZE		=	203,
	_CLR_SELECTED	=	211,
	_CLR_SAME_TYPE	=	212,
	_CLR_SAME_COLOR	=	213,
};
