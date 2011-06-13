#pragma once
#include "Sprite.h"


class Drawable
{

public:

	virtual void Draw()=0;
	bool operator==(const Drawable &Other)const;
	float getX()const;
	void setCord(float X,float Y);
	void setPosition(int X,int Y);
	void setX(float X);
	void setY(float Y);
	float getY()const;
	int getNaturalX()const;
	void setNaturalX(int X);
	void setNaturalY(int Y);
	int getNaturalY()const;
	unsigned int getID()const;
	void setID(unsigned int val);

protected:
	std::vector <Sprite> _sprites;

	float			_cordX;
	float			_cordY;
	int				_natuX;
	int				_natuY;
	unsigned int	_id;

};
