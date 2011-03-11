#include "Equiangular.h"


//=============================================================================
//
Equiangular::Equiangular(float x, float y,RgbColor &color)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE_R;
	_color = color;
}

//=============================================================================
//
void Equiangular::Draw()
{
	// Start drawing a Itriangle
	glBegin(GL_TRIANGLES);
	glColor3f(_color.r, _color.g, _color.b);                
	glVertex2f (_x, _y);										
	glVertex2f (_x - _size/2, _y - (_size * sin(M_PI/3)));//sqrt((double)3)\2));		
	glVertex2f (_x + _size/2, _y - (_size * sin(M_PI/3)));//sqrt((double)3)\2));				
	glEnd();
}