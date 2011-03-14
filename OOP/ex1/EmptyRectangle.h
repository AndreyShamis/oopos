//
//  @ Project : Paint
//  @ File Name : Empty Rectanle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "EmptyRectangle" shape at glut window
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH 0.1			// define default size of the 
									// EmptyRectangle shape side

class EmptyRectangle :public Shape	// class EmptyRectangle inherits from class 
									// Shape
{
public:
	// Constractor of class EmptyRectangle, get color and coordinat of start
	//	point to creat the shape.
	EmptyRectangle(float x, float y,const RgbColor &color);
	void Draw();					// Drow the shape: EmptyRectangle
};
