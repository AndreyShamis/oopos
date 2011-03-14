//
//  @ Project : Paint
//  @ File Name : Shape.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : An abstract class that reprisen Shapes at glut window
//
#pragma once
#include "macros.h"
#define MINIMAL_SIZE	0.01	// Define minimal size of hall shapes
class Shape
{
public:
	virtual void Draw()=0;		// virtual function for drowing shapes
	void IncreaseSize(const float &bySize);
	void ShrinkSize(const float &bySize);	
	RgbColor GetColor()const;				
	void SetColor(const RgbColor &color);
	void SetColor(const bool &selected);
	void SetSize(const float &newValue);
	float GetSize()const;
protected:

	// Define coordinate of shape
	float _x;
	float _y;
	
	float _size;				// Define size of shape
	RgbColor _color;			// Define color of shape
};