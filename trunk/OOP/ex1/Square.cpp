//
//  @ Project : Paint
//  @ File Name : Square.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Square" shape at glut window
//
#include "Square.h"

//=============================================================================
// Constractor of class Square, get color and coordinat of start point to creat 
// the shape.
Square::Square(float x, float y,const RgbColor &color)
{
	// set coordinats of shape
	_x		= x;
	_y		= y;

	_size	= DEFAULT_SIZE_SH;		// set default side size of shape
	_color = color;					// set color of shape
}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Square::Draw()
{
	glBegin(GL_QUADS);							// Start drawing a square
	glColor3f(_color.r, _color.g, _color.b);  	// Set color of shape 

	// set points of shape
	glVertex2f (_x, _y);
	glVertex2f (_x, _y - _size);
	glVertex2f (_x + _size , _y - _size);
	glVertex2f (_x + _size, _y);

	glEnd();									// End of drawing a vertical
}