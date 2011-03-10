#include "EmptyCircle.h"

//=============================================================================
//
EmptyCircle::EmptyCircle(float x, float y,RgbColor &color)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_RADIUS;
	_color = color;

}

//=============================================================================
//
void EmptyCircle::Draw()
{
	glBegin(GL_LINE_LOOP);

	float x, y;

	glColor3f(_color.r, _color.g, _color.b);			
		
	x = (float)_size * cos(359 * M_PI/180.0f);	
	y = (float)_size * sin(359 * M_PI/180.0f);	
	for(int j = 0; j < 30; j++)						// (360/12)
	{
		glVertex2f(x + _x, y + _y);
		x = (float)_size * cos(j * M_PI/15.0f);	// (180/12)
		y = (float)_size * sin(j * M_PI/15.0f);	// (180/12)
		glVertex2f(x + _x, y + _y);
	}
	glEnd(); 
} 