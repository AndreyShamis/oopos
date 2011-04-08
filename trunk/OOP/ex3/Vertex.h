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
	Vertex(const float X, const float Y,const int EdgesSize,const float dist);
	void SetID(const int val);
	void Draw();
	int GetID()const
	{
		return(_id);
	}
	float getX()const
	{
		return(_x);
	}
	float getY()const
	{
		return(_y);
	}

	void Shift()
	{
		bool first = _future_edge[0];
		_future_edge.erase(_future_edge.begin());
		_future_edge.push_back(first);
	}

	void ChangeEdge(const int place)
	{
		_future_edge[place] = true;
	}

	void LightOFF()
	{
		_lighted = false;
	}
	void LightON()
	{
		_lighted = true;
	}
private:
	float _x;
	float _y;
	bool  _lighted;
	int _id;
	float _dist;
	
	int MAX_VEC_SIZE;
	std::vector<bool> _future_edge;

};
