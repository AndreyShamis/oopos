
#include "macros.h"
#include "Equiangular.h"

Equiangular::Equiangular(float x, float y)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE_SH;
}


void Equiangular::Draw()
{
	// Start drawing a Equiangular

	glBegin(GL_TRIANGLES); 		
	glColor3f(0.0f,1.0f,0.0f);              
	glVertex2f (_x, _y);							
	glVertex2f (_x + _size * 2, _y);				
	glVertex2f (_x + _size * 2, _y - _size);		
	glVertex2f (_x, _y - _size);						
	glEnd();
}