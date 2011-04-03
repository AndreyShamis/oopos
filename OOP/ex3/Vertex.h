#pragma once
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
		;
	}
private:
	float _x;
	float _y;
	bool  _lighted;
	unsigned int _id;

};
