#include "Wheel.h"

//=============================================================================
//
Wheel::Wheel(float x,float y,const RgbColor &color)
{
	_x		= x;
	_y		= y;
	_size	= DEFAULT_RADIUS;
	_color = color;

}

//=============================================================================
//
void Wheel::Draw()
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(100);
	glColor3f(_color.r, _color.g, _color.b);  
	float x, y;
	for(int i=(int)(_size * 3000); i < (int)(_size * 3000 * 2); i++)
	{
		x = ((float)i/3000) * cos(359 * M_PI/180.0f);
		y = ((float)i/3000) * sin(359 * M_PI/180.0f);
		for(int j = 0; j < 30; j++)
		{
			glVertex2f(x + _x, y + _y);
			x = ((float)i/3000) * cos(j * M_PI/15.0f);
			y = ((float)i/3000) * sin(j * M_PI/15.0f);
			glVertex2f(x + _x, y + _y);
		}
	}
	glEnd(); 
	
} 