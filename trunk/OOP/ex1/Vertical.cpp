
#include "macros.h"
#include "Vertical.h"

Vertical::Vertical(float x, float y)
{
	_x		= x;
	_y		= y;
	_size	= DEFAULT_SIZE;
}


void Vertical::Draw()
{
	glBegin(GL_LINES);						// Start drawing a vertical

        glColor3f(0.0f, 1.0f, 0.0f);		      
		glVertex2f (_x, _y);				// down point  		
		glVertex2f (_x, _y + _size);		// up point		 
	glEnd();
}