#pragma once
#include "macros.h"
#include <vector>
#include "drawable.h"

class Vertex :public Drawable
{

public:
	bool operator==(const Vertex &other) const
	{
		if(_id == other._id)
			return(true);
 
		return(false);

	}

	Vertex(const float X, const float Y);
	~Vertex(void);
	void SetID(const int val)
	{
		_id = val;
	}

	void Draw()
	{


		//	Load geen

		// Start drawing a dot 
		glEnable(GL_POINT_SMOOTH);
		glPointSize(20.0);

		glBegin(GL_POINTS);
		//std::cout << "Draw\t";
		//std::cout << "X: " << _x << "\t:: Y: " << _y << "\n";
									// set point size
		glColor3f(0.0, 1.0, 0.0);	// Set color of shape
		glVertex2f (_x, _y);						// set point of shape		
		glEnd();									// End of drawing a vertical
	}

	int GetID()const
	{
		return(_id);
	}
private:
	float _x;
	float _y;
	bool  _lighted;
	unsigned int _id;

	std::vector<int> _future_edge;

};
