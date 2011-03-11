#include "Itriangle.h"

//=============================================================================
//
Itriangle::Itriangle(float x, float y, const RgbColor &color)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_HEIGHT;


	
	_color = color;
}

//=============================================================================
//
void Itriangle::Draw()
{
	// Start drawing a Itriangle
	glBegin(GL_TRIANGLES);
	glColor3f(_color.r, _color.g, _color.b);                
	glVertex2f (_x, _y);										
	glVertex2f (_x - (_size-0.1)/2, _y - _size);		
	glVertex2f (_x + (_size-0.1)/2, _y - _size);						
	glEnd();
}