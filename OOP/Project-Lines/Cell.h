#pragma once
#include "Sprite.h"


class Cell
{

public:
	bool operator==(const Cell &Other)const
	{
		return(Other.getID() == this->getID());
	}
	float getX()const
	{
		return(_cordX);
	}
	void setX(float X)
	{

		_cordX = X;
	}
	void setY(float Y)
	{

		_cordY = Y;
	}
	float getY()const
	{

		return(_cordY);
	}
	unsigned int getID()const
	{

		return(_id);
	}
	void setID(unsigned int val)
	{
		_id = val;
	}


protected:
	std::vector <Sprite> _sprites;

	float _cordX;
	float _cordY;
	unsigned int _id;

};
