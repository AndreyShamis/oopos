//
//
//  @ Project : Paint
//  @ File Name : Dot.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"
#define DEFAULT_SIZE_SH 0.1

class Dot :public Shape 
{
public:
	Dot(float x, float y,const RgbColor &color);
	void Draw();
};