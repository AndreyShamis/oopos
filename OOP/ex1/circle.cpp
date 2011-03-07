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
	float k = _x;
	float h = _y;
     
  for (int i = 0; i < 180; i++)
    {
		   glColor3f(0.0f,1.0f,0.0f);              // Синий
    float x = (float)(r*cos((float)i)) - h;
    float y = (float)(r*sin((float)i)) + k;
    glVertex3f(x+k,y - h,0);
    
    x = (float)(r*cos((float)i + 0.1)) - h;
    y = (float)(r*sin((float)i + 0.1)) + k;
    glVertex3f(x+k,y - h,0);
    }
	glEnd();	
}