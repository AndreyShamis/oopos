//
//  @ Project : Paint
//  @ File Name : Horizontal.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Horizontal" shape at glut window
//
#include "Horizontal.h"

//=============================================================================
// Constractor of class Horizontal, get color and coordinat of start point 
// to creat the shape.
Horizontal::Horizontal(float x, float y,const RgbColor &color)
{
	// set coordinats of shape
	_x = x;
	_y = y;

	_size = DEFAULT_SIZE_SH1;	// set default side size of shape 
	_color = color;				// set color of shape
}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Horizontal::Draw()
{
	glBegin(GL_LINES);							// Start drawing a Horizontal
	glColor3f(_color.r, _color.g, _color.b);  	// Set color of shape

	// set points of shape
	glVertex2f (_x, _y);					
	glVertex2f (_x + _size, _y);

	glEnd();									// End of drawing a vertical
}