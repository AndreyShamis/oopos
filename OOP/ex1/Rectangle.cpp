#include "Rectangle.h"

Rectangle::Rectangle(float x, float y,const RgbColor &color, bool isEmpty)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE_SH;
	_isEmpty	= isEmpty;
	_color = color;
}

void Rectangle::Draw()
{
	// Start drawing a Rectangle
	if(_isEmpty)
		glBegin(GL_LINES);
	else
		glBegin(GL_POLYGON);//GL_QUADS

	glColor3f(_color.r, _color.g, _color.b);  
	glVertex2f (_x, _y);
	glVertex2f (_x + _size * 2, _y);
	glVertex2f (_x + _size * 2, _y - _size);
	glVertex2f (_x, _y - _size);
	glEnd();
}