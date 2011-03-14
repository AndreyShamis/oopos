//
//  @ Project : Paint
//  @ File Name : Equiangular.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Equiangular" shape at glut window
//
#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#define DEFAULT_SIZE_R 0.2		// define default size of the Equiangular shape
								// side

class Equiangular :public Shape // class Equiangular inherits from class Shape 
{
public:
	// Constractor of class Equiangular, get color and coordinat of start point 
	// to creat the shape.
	Equiangular(float x, float y,RgbColor &color);
	void Draw();				// Drow the shape: Equiangular
};
