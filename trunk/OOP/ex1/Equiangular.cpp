//
//  @ Project : Paint
//  @ File Name : Equiangular.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Equiangular" shape at glut window
//
#include "Equiangular.h"

//=============================================================================
// Constractor of class Equiangular, get color and coordinat of start point 
// to creat the shape.
Equiangular::Equiangular(float x, float y,RgbColor &color)
{
	// set coordinats of shape
	_x			= x;
	_y			= y;

	_size		= DEFAULT_SIZE_R;	// set default side size of shape
	_color = color;					// set color of shape
}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Equiangular::Draw()
{
	glBegin(GL_TRIANGLES);						// Start drawing a equiangular
	glColor3f(_color.r, _color.g, _color.b);    // Set color of shape    

	// calculate and set points of shape
	glVertex2f (_x, _y);										
	glVertex2f (_x - _size/2, _y - (_size * sin(M_PI/3)));
	glVertex2f (_x + _size/2, _y - (_size * sin(M_PI/3)));	

	glEnd();									// End of drawing a vertical
}