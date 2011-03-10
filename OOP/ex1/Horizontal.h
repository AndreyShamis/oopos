//
//  @ Project : Paint
//  @ File Name : Horizontal.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"


#define DEFAULT_SIZE_SH1 0.2

class Horizontal :public Shape
{
public:
	Horizontal(float x, float y,const RgbColor &color);
	void Draw();
};