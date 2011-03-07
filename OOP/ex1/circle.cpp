#include "Circle.h"

Circle::Circle(float x,float y)
{
	_x=0.4;
	_y=0.6;
}

void Circle::Draw()
{
	glBegin(GL_LINES); // Start drawing a quad primitive
	
	float r = 0.2;  
	glColor3f(0.4f,1.4f,0.3f);              // Синий
	for (int i = 0; i < 180; i++)
	{
		glVertex2f(r*cos((float)i)+_x,r*sin((float)i)+_y);
		//glVertex2f(r*cos((float)-i)+_x,r*sin((float)-i)+_y);
	}

	glEnd();	
}