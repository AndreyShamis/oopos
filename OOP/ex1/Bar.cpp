
#include "macros.h"
#include "bar.h"

Bar::Bar(float x, float y)
{
	_x=0.2;
	_y=0.3;
}


void Bar::Draw()
{
	glBegin(GL_QUADS); // Start drawing a quad primitive

        glColor3f(0.0f,1.0f,0.0f);              // Синий
		glVertex2f (_x, _y);           //left down
		glVertex2f (_x+SIDE_SIZE, _y);			// right down
		glVertex2f (_x+SIDE_SIZE, _y-SIDE_SIZE);			//	right up
		glVertex2f (_x, _y-SIDE_SIZE);			//	left up
	glEnd();
}