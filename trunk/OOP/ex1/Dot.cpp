#include "Dot.h"

//=============================================================================
//
Dot::Dot(float x, float y,const RgbColor &color)
{
	_x		= x;
	_y		= y;
	_size	= DEFAULT_SIZE_SH;
	_color = color;
}

//=============================================================================
//
void Dot::Draw()
{
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS); 
	glPointSize(_size);
	glColor3f(_color.r, _color.g, _color.b); 
	glVertex2f (_x, _y);			
	glEnd();
}