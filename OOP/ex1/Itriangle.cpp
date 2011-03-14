//
//  @ Project : Paint
//  @ File Name : bar.cpp
//  @ Date : 3/3/2011
//  @ Author :	 Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Itrriangle" shape at glut window
//
#include "Itriangle.h"

//=============================================================================
// Constractor of class Itrriangle, get color and coordinat of start point 
// to creat the shape.
Itriangle::Itriangle(float x, float y, const RgbColor &color)
{
	// set coordinats of shape
	_x			= x;
	_y			= y;

	_size		= DEFAULT_HEIGHT;	// set default height of shape
	_color = color;					// set color of shape
}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Itriangle::Draw()
{
	glBegin(GL_TRIANGLES);						  // Start drawing a Itriangle
	glColor3f(_color.r, _color.g, _color.b);	  // Set color of shape

	// set points of shape
	glVertex2f (_x, _y);										
	glVertex2f (_x - DEFAULT_BASE/2, _y - _size);		
	glVertex2f (_x + DEFAULT_BASE/2, _y - _size);	

	glEnd();									  // End of drawing a vertical
}