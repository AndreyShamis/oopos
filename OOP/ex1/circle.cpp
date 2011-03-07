#include "Circle.h"

Circle::Cycle(float x,float y)
{
	_x=0.4;
	_y=0.6;
}

Circle::Draw()
{
	glBegin(GL_POLYGON); // Start drawing a quad primitive

        glColor3f(0.0f,1.0f,0.0f);              // Синий
		glVertex2f (_x, _y-SIDE_SIZE);           //left down
		glVertex2f (_x+SIDE_SIZE, _y-_x+SIDE_SIZE);			// right down
		glVertex2f (_x+SIDE_SIZE, _y);			//	right up
		glVertex2f (_x, _y);			//	left up
	glEnd();	
}