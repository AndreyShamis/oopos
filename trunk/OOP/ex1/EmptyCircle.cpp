//
//  @ Project : Paint
//  @ File Name : Empty Cicle.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "EmptyCircle" shape at glut window
//
#include "EmptyCircle.h"

//=============================================================================
// Constractor of class EmptyCircle, get color and coordinat of start point 
// to creat the shape.
EmptyCircle::EmptyCircle(float x, float y,RgbColor &color)
{
	// set coordinats of shape
	_x			= x;
	_y			= y;

	_size		= DEFAULT_RADIUS;			// set default radius of shape 
	_color		= color;					// set color of shape

}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void EmptyCircle::Draw()
{
	glBegin(GL_LINE_LOOP);						// Start drawing a empty circle
	glColor3f(_color.r, _color.g, _color.b);	// Set color of shape

	// calculate and set points of shape

	float x, y;									// temp point for calculation

	x = (float)_size * cos(359 * M_PI/180.0f);	
	y = (float)_size * sin(359 * M_PI/180.0f);	

	// loop for drowing sides of circle
	for(int j = 0; j < 30; j++)					// (360/12)
	{
		glVertex2f(x + _x, y + _y);
		x = (float)_size * cos(j * M_PI/15.0f);	// (180/12)
		y = (float)_size * sin(j * M_PI/15.0f);	// (180/12)
		glVertex2f(x + _x, y + _y);
	}
	glEnd(); 									// End of drawing a vertical
} 