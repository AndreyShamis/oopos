#include "Vertex.h"

float Vertex::rads = (3.1415926535/180);

//=============================================================================
//	Constructor 
//	Get coordinates X and Y , size of potential neighbors vector and minimal 
//	distance between two vertex
Vertex::Vertex(const float X, const float Y,
			   const int EdgesSize,const float dist)
{
	_x = X;					//	Set coordinates
	_y = Y;					//	Set coordinates
	_dist = dist;			//	Distrance between vertexs
	 MAX_VEC_SIZE = EdgesSize;	//	Max neighobrs
	//	Set potential vector of neighbors
	for(int i =0;i<MAX_VEC_SIZE;i++)
	{
		_future_edge.push_back(false);
	}
}
//=============================================================================
//	Return Unique Id of vertex in Graph
int Vertex::GetID()const
{
	return(_id);
}
//=============================================================================
//	Return X coordinate
float Vertex::getX()const
{
	return(_x);
}
//=============================================================================
//	Return Y coordinate
float Vertex::getY()const
{
	return(_y);
}
//=============================================================================
//	Put first value to end of vector from start
void Vertex::Shift()
{
	bool first = _future_edge[0];
	_future_edge.erase(_future_edge.begin());
	_future_edge.push_back(first);
}
//=============================================================================
//	Change value in array of potential neighobrs
void Vertex::ChangeEdge(const int place)
{
	_future_edge[place] = true;
}
//=============================================================================
//	Turn off the vertex be lighted
void Vertex::LightOFF()
{
	_lighted = false;
}
//=============================================================================
//	Turn on the vertex be lighted
void Vertex::LightON()
{
	_lighted = true;
}
//=============================================================================
//	NOT USED
void Vertex::setFather(const int value)
{
	_father = value;
}
//=============================================================================
//	Return vector of potential neighbors
const std::vector<bool> Vertex::getFutEdg()const
{
	return(_future_edge);
}
//=============================================================================
//	Operator comparation between two vertexs by they uniqie ID
bool Vertex::operator==(const Vertex &other) const
{
	if(_id == other._id)
		return(true);

	return(false);

}
//=============================================================================
//	Set id of vertex in graph
void Vertex::SetID(const int val)
{
	_id = val;
}
//=============================================================================
//	Function to drow the vertex
void Vertex::Draw()
{
	const float hfSz =	 _dist/2;				//	get Helf size between
												//	two neigbors
	const float proportion = 360/MAX_VEC_SIZE;	//	angle between neighobrs
	const int vecSize = (int)_future_edge.size();	//	Get vector size
	for(int i=0;i<vecSize;i++)
	{
		if(_future_edge[i])
		{
			glBegin(GL_LINES);							// Start drawing a vertical
			glColor3f(0.4, 0.8, 0.0);  	// Set color of shape
			// set points of shape
			glVertex2f (_x, _y);								
			glVertex2f (_x - hfSz*cos(float(i*proportion)*rads), _y - hfSz*sin(float(i*proportion)*rads));	
			glEnd();									// End of drawing a vertical
		}
	}

	// Start drawing a dot 
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
								// set point size
	if(_lighted)
		glColor3f(1.0, 1.0, 0.0);	// Set color of shape
	else
		glColor3f(0.3, 0.4, 0.0);	// Set color of shape
	glVertex2f (_x, _y);						// set point of shape		

	glEnd();									// End of drawing a vertical

}
