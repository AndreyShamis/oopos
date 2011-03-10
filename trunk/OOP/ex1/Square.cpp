#include "Square.h"

//=============================================================================
//
Square::Square(float x, float y,const RgbColor &color)
{
	_x		= x;
	_y		= y;
	_size	= DEFAULT_SIZE_SH;
	_color = color;
}

//=============================================================================
//
void Square::Draw()
{
	glBegin(GL_QUADS); // Start drawing a quad primitive
	glColor3f(_color.r, _color.g, _color.b);  
	glVertex2f (_x, _y);
	glVertex2f (_x, _y - _size);
	glVertex2f (_x + _size , _y - _size);
	glVertex2f (_x + _size, _y);
	glEnd();
}