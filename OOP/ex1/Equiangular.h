//
//  @ Project : Paint
//  @ File Name : Equiangular.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH 0.2

class Equiangular :public Shape 
{
public:
	Equiangular(float x, float y,RgbColor &color);
	void Draw();
};
