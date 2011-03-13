//
//  @ Project : Paint
//  @ File Name : Square.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#pragma once
#include "shape.h"


#define DEFAULT_SIZE_SH 0.1

class Square :public Shape 
{
public:
	Square(float x, float y,const RgbColor &color);
	void Draw();
};