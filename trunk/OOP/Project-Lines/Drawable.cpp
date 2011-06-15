#include "Drawable.h"
//=============================================================================
//		Get float coordinate of X
float Drawable::getX()const
{
	return(_cordX);
}
//=============================================================================
//		set float coordinate of X and Y
void Drawable::setCord(float X,float Y)
{
	_cordX = X;
	_cordY = Y;
}

//=============================================================================
//		Set float coordinate of X
void Drawable::setX(float X)
{
	_cordX = X;
}
//=============================================================================
//		Get float coordinate of Y
void Drawable::setY(float Y)
{
	_cordY = Y;
}
//=============================================================================
//		Get float coordinate of Y
float Drawable::getY()const
{
	return(_cordY);
}

