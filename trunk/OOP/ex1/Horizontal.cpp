#include "Horizontal.h"

//=============================================================================
//
Horizontal::Horizontal(float x, float y,const RgbColor &color)
{
	_x = x;
	_y = y;
	_size = DEFAULT_SIZE_SH1;
	_color = color;
}

//=============================================================================
//
void Horizontal::Draw()
{
	glBegin(GL_LINES);				// Start drawing a Horizontal
	glColor3f(_color.r, _color.g, _color.b);  		      
	glVertex2f (_x, _y);			// left point  		
	glVertex2f (_x + _size, _y);	// right point		 
	glEnd();
}