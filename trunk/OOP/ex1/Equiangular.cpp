#include "Equiangular.h"

Equiangular::Equiangular(float x, float y,RgbColor &color)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE_SH;
	_color = color;
}


void Equiangular::Draw()
{
	// Start drawing a Equiangular

	glBegin(GL_TRIANGLES); 		
	glColor3f(_color.r, _color.g, _color.b);              
	glVertex2f (_x, _y);							
	glVertex2f (_x + _size * 2, _y);				
	glVertex2f (_x + _size * 2, _y - _size);		
	glVertex2f (_x, _y - _size);						
	glEnd();
}