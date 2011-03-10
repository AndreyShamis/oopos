#include "Vertical.h"

//=============================================================================
//
Vertical::Vertical(float x, float y,const RgbColor &color)
{
	_x		= x;
	_y		= y;
	_size	= DEFAULT_SIZE_SH2;
	_color = color;
} 

//=============================================================================
//
void Vertical::Draw()
{
	glBegin(GL_LINES);						// Start drawing a vertical
	glColor3f(_color.r, _color.g, _color.b);  		      
	glVertex2f (_x, _y);				// down point  		
	glVertex2f (_x, _y + _size);		// up point		 
	glEnd();
}