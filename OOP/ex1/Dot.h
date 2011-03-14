//
//
//  @ Project : Paint
//  @ File Name : Dot.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Dot" shape at glut window
//
#pragma once
#include "shape.h"
#define DEFAULT_SIZE_SH 0.1		// define default radius of the Dot shape

class Dot :public Shape			// class Dot inherits from class Shape 
{
public:
	// Constractor of class Dot, get color and coordinat of start point to
	// creat the shape.
	Dot(float x, float y,const RgbColor &color);
	void Draw();				// Drow the shape: Dot
};