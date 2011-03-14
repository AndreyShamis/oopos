//
//  @ Project : Paint
//  @ File Name : Square.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A class that reprisen "Square" shape at glut window
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH 0.1		// define default size of the Square shape side

class Square :public Shape		// class Square inherits from class Shape 
{
public:
	// Constractor of class Square, get color and coordinat of start point to
	// creat the shape.
	Square(float x, float y,const RgbColor &color);
	void Draw();				// Drow the shape: Square
};