#pragma once
#include "Drawable.h"
class Dragable : public Drawable
{
public:
	Dragable(){;};
	void setPosition(int X,int Y);
	int getNaturalX()const;
	void setNaturalX(int X);
	void setNaturalY(int Y);
	int getNaturalY()const;
	bool operator==(const Dragable &Other)const;
	unsigned int getID()const;
	void setID(unsigned int val);
protected:
	int				_natuX;
	int				_natuY;
	unsigned int	_id;
};
