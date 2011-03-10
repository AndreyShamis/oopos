//
//  @ Project : Paint
//  @ File Name : Empty Cicle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_RADIUS 0.1
class EmptyCircle : public Shape
{
public:
	EmptyCircle(float x, float y,RgbColor &color);
	void Draw();
};