#include "Circle.h"

Circle::Circle(float x,float y,bool hole)
{
	_x=x;
	_y=y;
	_haveHole = hole;
	_radius = DEFAULT_RADIUS;
}

void Circle::Draw()
{
	if(_haveHole)
		glBegin(GL_LINES); 
	else
		glBegin(GL_POLYGON); 
	  
	glColor3f(0.4f,1.4f,0.3f);              // Синий
	for (int i = 0; i < 3000; i++)
	{
		glVertex2f(_radius*cos((float)i)+_x,_radius*sin((float)i)+_y);
		//glVertex2f(r*cos((float)-i)+_x,r*sin((float)-i)+_y);
	}

	glEnd();	
}