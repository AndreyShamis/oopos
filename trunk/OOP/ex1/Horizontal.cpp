
#include "macros.h"
#include "Horizontal.h"

Horizontal::Horizontal(float x, float y)
{
	_x = x;
	_y = y;
	_size = DEFAULT_SIZE_SH1;
}


void Horizontal::Draw()
{
	glBegin(GL_LINES);				// Start drawing a Horizontal
	glColor3f(0.0f, 1.0f, 0.0f);		      
	glVertex2f (_x, _y);			// left point  		
	glVertex2f (_x + _size, _y);	// right point		 
	glEnd();
}