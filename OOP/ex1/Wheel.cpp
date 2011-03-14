//
//  @ Project : Paint
//  @ File Name : Wheel.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Wheel" shape at glut window
//
#include "Wheel.h"

//=============================================================================
// Constractor of class Wheel, get color and coordinat of start point to
// creat the shape.
Wheel::Wheel(float x,float y,const RgbColor &color)
{
	// set coordinats of shape
	_x		= x;
	_y		= y;

	_size	= DEFAULT_RADIUS;			// set default radius of shape 
	_color = color;						// set color of shape

}

//=============================================================================
// implementation of virtual function that drow the shape at glut window
// get nothing
// return nothing
void Wheel::Draw()
{
	glBegin(GL_LINE_LOOP);						// Start drawing a wheel
	glColor3f(_color.r, _color.g, _color.b);	// Set color of shape

	// calculate and set points of shape

	float x, y;									// temp point for calculation

	// loop for drowing internal circles
	for(int i=(int)(_size * 3000); i < (int)(_size * 3000 * 2); i++)
	{
		x = ((float)i/3000) * cos(359 * M_PI/180.0f);
		y = ((float)i/3000) * sin(359 * M_PI/180.0f);

		// loop for drowing single circle
		for(int j = 0; j < 30; j++)
		{
			glVertex2f(x + _x, y + _y);
			x = ((float)i/3000) * cos(j * M_PI/15.0f);
			y = ((float)i/3000) * sin(j * M_PI/15.0f);
			glVertex2f(x + _x, y + _y);
		}
	}
	glEnd();									// End of drawing a vertical
	
} 