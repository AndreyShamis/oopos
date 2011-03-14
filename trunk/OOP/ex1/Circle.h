//
//  @ Project : Paint
//  @ File Name : Circle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Circle" shape at glut window
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_RADIUS 0.1		// define default radius of the Circle shape

class Circle : public Shape		// class Circle inherits from class Shape
{
public:
	// Constractor of class Circle, get color and coordinat of start point to
	// creat the shape.
	Circle(float x, float y,RgbColor &color);
	void Draw();				// Drow the shape: Circle
};
