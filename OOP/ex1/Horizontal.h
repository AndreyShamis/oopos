//
//  @ Project : Paint
//  @ File Name : Horizontal.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Horizontal" shape at glut window
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH1 0.2	// define default size of the Horizontale shape
								// side

class Horizontal :public Shape	// class Horizontal inherits from class Shape 
{
public:
	// Constractor of class Horizontal, get color and coordinat of start point 
	// to creat the shape.
	Horizontal(float x, float y,const RgbColor &color);
	void Draw();				// Drow the shape: Horizontal
};