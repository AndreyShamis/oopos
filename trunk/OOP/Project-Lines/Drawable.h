#pragma once
#include "Sprite.h"


class Drawable
{

public:

	virtual void Draw()=0;
	bool operator==(const Drawable &Other)const
	{
		return(Other.getID() == this->getID());
	}
	float getX()const
	{
		return(_cordX);
	}
	void setCord(float X,float Y)
	{
		_cordX = X;
		_cordY = Y;
	}
	void setPosition(int X,int Y)
	{
		_natuX = X;
		_natuY = Y;
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
	int getNaturalX()const
	{
		return(_natuX);
	}
	void setNaturalX(int X)
	{

		_natuX = X;
	}
	void setNaturalY(int Y)
	{
		_natuY = Y;
	}
	int getNaturalY()const
	{
		return(_natuY);
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

	float			_cordX;
	float			_cordY;
	int				_natuX;
	int				_natuY;
	unsigned int	_id;

};
