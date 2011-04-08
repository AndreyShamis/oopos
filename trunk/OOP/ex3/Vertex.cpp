#include "Vertex.h"

Vertex::Vertex(const float X, const float Y,const int EdgesSize)
{
	_x = X;
	_y = Y;

	for(int i =0;i<EdgesSize;i++)
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
	// Start drawing a dot 
	glEnable(GL_POINT_SMOOTH);
	glPointSize(500);

	glBegin(GL_POINTS);
	//std::cout << "Draw\t";
	//std::cout << "X: " << _x << "\t:: Y: " << _y << "\n";
								// set point size
	glColor3f(1.0, 1.0, 0.0);	// Set color of shape
	glVertex2f (_x, _y);						// set point of shape		
	glEnd();									// End of drawing a vertical
}
