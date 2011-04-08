#include "Vertex.h"

Vertex::Vertex(const float X, const float Y,const int EdgesSize,const float dist)
{
	_x = X;
	_y = Y;
	_dist = dist;
	 MAX_VEC_SIZE = EdgesSize;
	for(int i =0;i<MAX_VEC_SIZE;i++)
	{
		_future_edge.push_back(false);
	}
}
void Vertex::SetID(const int val)
{
	_id = val;
}
void Vertex::Draw()
{

	for(int i=0;i<(int)_future_edge.size();i++)
	{
		if(_future_edge[i])
		{
			glBegin(GL_LINES);							// Start drawing a vertical
			glColor3f(0.4, 0.8, 0.0);  	// Set color of shape

			// set points of shape

			glVertex2f (_x, _y);								
			glVertex2f (_x -(_dist/2)*cos(float(i*360/MAX_VEC_SIZE)*(3.1415926535/180)), _y - (_dist/2)*sin(float(i*360/MAX_VEC_SIZE)*(3.1415926535/180)));	

			glEnd();									// End of drawing a vertical
		}
	}

	// Start drawing a dot 
	glEnable(GL_POINT_SMOOTH);
	glPointSize(20);

	glBegin(GL_POINTS);
	//std::cout << "Draw\t";
	//std::cout << "X: " << _x << "\t:: Y: " << _y << "\n";
								// set point size
	if(_lighted)
		glColor3f(1.0, 1.0, 0.0);	// Set color of shape
	else
		glColor3f(0.3, 0.6, 0.0);	// Set color of shape
	glVertex2f (_x, _y);						// set point of shape		

	glEnd();									// End of drawing a vertical

}
