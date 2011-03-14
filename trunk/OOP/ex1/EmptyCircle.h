//
//  @ Project : Paint
//  @ File Name : Empty Cicle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "EmptyCircle" shape at glut window
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_RADIUS 0.1			// define default radius of the EmptyCircle
									// shape

class EmptyCircle : public Shape	// class EmptyCircle inherits from class
									// Shape
{
public:
	// Constractor of class EmptyCircle, get color and coordinat of start point 
	// to creat the shape.
	EmptyCircle(float x, float y,RgbColor &color);
	void Draw();					// Drow the shape: EmptyCircle
};