//
//  @ Project : Paint
//  @ File Name : Circle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_RADIUS 0.1
class Circle : public Shape
{
public:
	Circle(float x, float y,RgbColor &color);
	void Draw();
};
