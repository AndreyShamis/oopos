#pragma once
#include "Sprite.h"


class Drawable
{

public:

	virtual void Draw()=0;
	float getX()const;
	void setX(float X);
	void setY(float Y);
	float getY()const;
	void setCord(float X,float Y);
protected:
	std::vector <Sprite> _sprites;
	float			_cordX;
	float			_cordY;


};
