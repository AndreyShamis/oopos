//
//  @ Project : Paint
//  @ File Name : Wheel.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Wheel" shape at glut window
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_RADIUS 0.1		// define default radius of the Wheel shape 

class Wheel : public Shape		// class Wheel inherits from class Shape
{
public:
	// Constractor of class Wheel, get color and coordinat of start point to
	// creat the shape.
	Wheel(float x ,float y,const RgbColor &color);
	void Draw();				// Drow the shape: Whell
};