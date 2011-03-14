//
//  @ Project : Paint
//  @ File Name : Shape.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : An abstract class that reprisen Shapes at glut window
//
#include "Shape.h"
//=============================================================================
// function that increase size of shapes 
// get size of shape by ref
// return nothing
void Shape::IncreaseSize(const float &bySize)
{
	_size+=bySize;		// increase the size of shape

}

//=============================================================================
// function that shrink size of shapes 
// get size of shape by ref
// return nothing
void Shape::ShrinkSize(const float &bySize)
{
	// privemt shrinking more than minimal size of shape
	if(_size-bySize>MINIMAL_SIZE)
		_size-=bySize;			// shrink the size of shape
	else
		_size = MINIMAL_SIZE;	// set size of shape to minimal size
}

//=============================================================================
// function that retern the color of the shape
// get nothing
RgbColor Shape::GetColor()const
{
	return _color;		// retern the color of the shape
}

//=============================================================================
// function that set the color of the shape
// get color rgbcolor type by ref
// return nothing
void Shape::SetColor(const RgbColor &color)
{
	_color = color;		// set the color of the shape
}

//=============================================================================
// function that set the size of the shape
// get size by ref
// return nothing
void Shape::SetSize(const float &newValue)
{
	_size = newValue;	// set size
}

//=============================================================================
// function that retern the size of the shape
// return size of shape
// get nothing
float Shape::GetSize()const
{
	return(_size);		// return size of shape

}