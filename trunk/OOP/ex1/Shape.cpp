#include "Shape.h"
Shape::Shape()
{
	;
}

//=============================================================================
//
void Shape::IncreaseSize(const float &bySize)
{
	_size+=bySize;

}

//=============================================================================
//
void Shape::ShrinkSize(const float &bySize)
{
	if(_size-bySize>0)
		_size-=bySize;
	else
		_size = MINIMAL_SIZE;
}

//=============================================================================
//
RgbColor Shape::GetColor()const
{
	return _color;
}

//=============================================================================
//
void Shape::SetColor(const RgbColor &color)
{
	_color = color;
}

//=============================================================================
//
void Shape::SetSize(const float &newValue)
{
	_size = newValue;
}

//=============================================================================
//
float Shape::GetSize()const
{
	return(_size);

}