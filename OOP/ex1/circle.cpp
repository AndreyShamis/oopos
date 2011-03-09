#include "Circle.h"

Circle::Circle(float x, float y,RgbColor &color, bool isEmpty)
{
	_x			= x;
	_y			= y;
	_isEmpty	= isEmpty;
	_size		= DEFAULT_RADIUS;
	_color = color;

}

void Circle::Draw()
{
	if(_isEmpty) 
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_POLYGON);

	float x, y;

	//glColor3f(0.4f, 1.4f, 0.3f);				//green
	glColor3f(_color.r, _color.g, _color.b);				// black
		
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


