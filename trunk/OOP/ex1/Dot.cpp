//
//  @ Project : Paint
//  @ File Name : Dot.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Dot" shape at glut window
//
#include "Dot.h"

//=============================================================================
// Constractor of class Dot, get color and coordinat of start point to
// creat the shape.
Dot::Dot(float x, float y,const RgbColor &color)
{
	// set coordinats of shape
	_x		= x;
	_y		= y;

	_size	= DEFAULT_SIZE_SH;			// set default side size of shape 
	_color = color;						// set color of shape
}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Dot::Draw()
{
	// Start drawing a dot 
	glEnable(GL_POINT_SMOOTH);					
	glBegin(GL_POINTS);

	glPointSize(_size);							// set point size
	glColor3f(_color.r, _color.g, _color.b);	// Set color of shape
	glVertex2f (_x, _y);						// set point of shape		
	glEnd();									// End of drawing a vertical
}