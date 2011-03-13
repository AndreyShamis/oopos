//
//  @ Project : Paint
//  @ File Name : Shape.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "macros.h"
#define MINIMAL_SIZE	0.01
class Shape
{
public:
	virtual void Draw()=0;
	void IncreaseSize(const float &bySize);
	void ShrinkSize(const float &bySize);
	RgbColor GetColor()const;
	void SetColor(const RgbColor &color);
	bool GetSelected()const;
	void SetColor(const bool &selected);
	void SetSize(const float &newValue);
	float GetSize()const;
protected:
	float _x;
	float _y;
	float _size;
	RgbColor _color;
};