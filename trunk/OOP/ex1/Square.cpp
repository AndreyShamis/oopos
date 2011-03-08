
#include "macros.h"
#include "Square.h"

Square::Square(float x, float y)
{
	_x		= x;
	_y		= y;
	_size	= DEFAULT_SIZE;
}


void Square::Draw()
{
	glBegin(GL_QUADS); // Start drawing a quad primitive

        glColor3f(0.0f,1.0f,0.0f);						// green
		glVertex2f (_x, _y);							// left down
		glVertex2f (_x + _size, _y);					// right down
		glVertex2f (_x + _size, _y - _size);			// right up
		glVertex2f (_x, _y - _size);					// left up
	glEnd();
}