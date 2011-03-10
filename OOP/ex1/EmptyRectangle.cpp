#include "EmptyRectangle.h"

//=============================================================================
//
EmptyRectangle::EmptyRectangle(float x, float y,const RgbColor &color)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE_SH;
	_color = color;
}

//=============================================================================
//
void EmptyRectangle::Draw() 
{
	glBegin(GL_LINE_LOOP);
	glColor3f(_color.r, _color.g, _color.b);  
	glVertex2f (_x, _y);
	glVertex2f (_x, _y - _size);
	glVertex2f (_x + (_size * 2), _y - _size);
	glVertex2f (_x + (_size * 2), _y);
	glEnd();
}