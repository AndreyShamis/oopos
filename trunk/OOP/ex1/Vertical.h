//
//  @ Project : Paint
//  @ File Name : Vertical.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinsk
//	@ Description : A class that reprisen "Vertical Side" shape at glut window
//
//
#pragma once
#include "shape.h"

#define DEFAULT_SIZE_SH2 0.2	// define default size of the Vertical side

class Vertical :public Shape	// class Vertical inherits from class Shape 
{
public:
	// Constractor of class Vertical, get color and coordinat of start point to
	// creat the shape.
	Vertical(float x, float y,const RgbColor &color);
	void Draw();				// Drow the shape: Vertical side
};