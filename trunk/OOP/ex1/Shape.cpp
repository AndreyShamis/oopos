#include "Shape.h"


Shape::Shape()
{
	;
}

void Shape::IncreaseSize(const float &bySize)
{

	_size+=bySize;

}

void Shape::ShrinkSize(const float &bySize)
{
	if(_size-bySize>0)
		_size-=bySize;
	else
		_size = 0.1;

}
