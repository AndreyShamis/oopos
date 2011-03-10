//
//  @ Project : Paint
//  @ File Name : Rectanglle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH 0.1

class Rectanglle :public Shape
{
public:
	Rectanglle(float x, float y,const RgbColor &color);
	void Draw();
};