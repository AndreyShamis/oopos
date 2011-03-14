//
//  @ Project : Paint
//  @ File Name : bar.h
//  @ Date : 3/3/2011
//  @ Author :	 Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Itrriangle" shape at glut window
//
#pragma once
#include "shape.h"

#define DEFAULT_HEIGHT	0.3		// define default size of the Itrriangle heigh
#define DEFAULT_BASE	0.2		// define default size of the Itrriangle base
								// side

class Itriangle :public Shape	// class Itrriangle inherits from class Shape 
{
public:
	// Constractor of class Itrriangle, get color and coordinat of start point 
	// to creat the shape.
	Itriangle(float x, float y,const RgbColor &color);
	void Draw();				// Drow the shape: Itrriangle
};
