#include "Drawable.h"

//=============================================================================
// Constructor
bool Drawable::operator==(const Drawable &Other)const
{
	return(Other.getID() == this->getID());
}
//=============================================================================
//
float Drawable::getX()const
{
	return(_cordX);
}
//=============================================================================
//
void Drawable::setCord(float X,float Y)
{
	_cordX = X;
	_cordY = Y;
}
//=============================================================================
//
void Drawable::setPosition(int X,int Y)
{
	_natuX = X;
	_natuY = Y;
}
//=============================================================================
//
void Drawable::setX(float X)
{

	_cordX = X;
}
//=============================================================================
//
void Drawable::setY(float Y)
{
	_cordY = Y;
}
//=============================================================================
//
float Drawable::getY()const
{
	return(_cordY);
}
//=============================================================================
//
int Drawable::getNaturalX()const
{
	return(_natuX);
}
//=============================================================================
//
void Drawable::setNaturalX(int X)
{

	_natuX = X;
}
//=============================================================================
//
void Drawable::setNaturalY(int Y)
{
	_natuY = Y;
}
//=============================================================================
//
int Drawable::getNaturalY()const
{
	return(_natuY);
}
//=============================================================================
//
unsigned int Drawable::getID()const
{
	return(_id);
}
//=============================================================================
//
void Drawable::setID(unsigned int val)
{
	_id = val;
}