//
//  @ Project : Paint
//  @ File Name : Vertical.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH2 0.2

class Vertical :public Shape 
{
public:
	Vertical(float x, float y,const RgbColor &color);
	void Draw();
};