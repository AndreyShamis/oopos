#include "Dragable.h"
//=============================================================================
//		Set natural coordinate of X and Y
void Dragable::setPosition(int X,int Y)
{
	_natuX = X;
	_natuY = Y;
}
//=============================================================================
//		Get natural coordinate of X 
int Dragable::getNaturalX()const
{
	return(_natuX);
}
//=============================================================================
//		Set natural coordinate of X 
void Dragable::setNaturalX(int X)
{

	_natuX = X;
}
//=============================================================================
//		Set natural coordinate of Y
void Dragable::setNaturalY(int Y)
{
	_natuY = Y;
}
//=============================================================================
//		Get natural coordinate of Y
int Dragable::getNaturalY()const
{
	return(_natuY);
}
//=============================================================================
//		Funcntion to get ID of object
unsigned int Dragable::getID()const
{
	return(_id);
}
//=============================================================================
//		Function for set ID of object
void Dragable::setID(unsigned int val)
{
	_id = val;
}
//=============================================================================
//		Operator of compare
bool Dragable::operator==(const Dragable &Other)const
{
	return(Other.getID() == this->getID());
}