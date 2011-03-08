
#include "macros.h"
#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, bool isEmpty)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE;
	_isEmpty	= isEmpty;
}


void Rectangle::Draw()
{
	// Start drawing a rectangel
	if(_isEmpty)
		glBegin(GL_QUADS);
	else
		glBegin(GL_LINES);
		 		
        glColor3f(0.0f,1.0f,0.0f);              
		glVertex2f (_x, _y);							
		glVertex2f (_x + _size * 2, _y);				
		glVertex2f (_x + _size * 2, _y - SIDE_SIZE);		
		glVertex2f (_x, _y - _size);						
	glEnd();
}