//
//  @ Project : Paint
//  @ File Name : bar.h
//  @ Date : 3/3/2011
//  @ Author :	 Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"
#define DEFAULT_HEIGHT 0.3
#define DEFAULT_BASE	0.2

class Itriangle :public Shape 
{
public:
	Itriangle(float x, float y,const RgbColor &color);
	void Draw();
};
