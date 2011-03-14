//
//  @ Project : Paint
//  @ File Name : Vertical.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinsk
//	@ Description : A class that reprisen "Vertical Side" shape at glut window
//
#include "Vertical.h"

//=============================================================================
// Constractor of class Vertical, get color and coordinat of start point to
// creat the shape.
Vertical::Vertical(float x, float y,const RgbColor &color)
{
	// set coordinats of shape
	_x		= x;
	_y		= y;

	_size	= DEFAULT_SIZE_SH2;		// set default side size of shape 
	_color = color;					// set color of shape
} 

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Vertical::Draw()
{
	glBegin(GL_LINES);							// Start drawing a vertical
	glColor3f(_color.r, _color.g, _color.b);  	// Set color of shape

	// set points of shape
	glVertex2f (_x, _y);								
	glVertex2f (_x, _y + _size);	

	glEnd();									// End of drawing a vertical
}