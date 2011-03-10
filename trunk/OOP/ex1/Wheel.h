//
//  @ Project : Paint
//  @ File Name : Wheel.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_RADIUS 0.1
class Wheel : public Shape
{
public:
	Wheel(float x ,float y,const RgbColor &color);
	void Draw();
};