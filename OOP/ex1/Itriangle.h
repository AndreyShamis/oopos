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

#if !defined(_ITRIANGLE_H)
#define _ITRIANGLE_H

#define DEFAULT_HEIGHT 0.3

class Itriangle :public Shape 
{
public:
	Itriangle(float x, float y,const RgbColor &color);
	void Draw();
};

#endif  //_ITRIANGLE_H