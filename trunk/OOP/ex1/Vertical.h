//
//
//  Generated by Andrey Shamis Ilia Gaysinski
//
//  @ Project : Paint
//  @ File Name : bar.h
//  @ Date : 3/3/2011
//  @ Author : 
//
//

#include "shape.h"

#if !defined(_VERTICAL_H)
#define _VERTICAL_H

#define DEFAULT_SIZE 0.2f

class Vertical :public Shape 
{
public:
	Vertical(float x, float y);
	void Draw();
};

#endif  //_VERTICAL_H
