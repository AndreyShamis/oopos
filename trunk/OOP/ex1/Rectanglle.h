//
//  @ Project : Paint
//  @ File Name : Rectanglle.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Rectanglle" shape at glut window
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH 0.1		// define default size of the Rectanglle shape
								// side

class Rectanglle :public Shape	// class Rectanglle inherits from class Shape 
{
public:
	// Constractor of class Rectanglle, get color and coordinat of start point 
	// to creat the shape.
	Rectanglle(float x, float y,const RgbColor &color);
	void Draw();				// Drow the shape: Rectanglle
};