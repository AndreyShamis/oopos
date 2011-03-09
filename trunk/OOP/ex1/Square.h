//
//  @ Project : Paint
//  @ File Name : bar.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//

#include "shape.h"

#if !defined(_SQUARE_H)
#define _SQUARE_H

#define DEFAULT_SIZE_SH 0.1

class Square :public Shape 
{
public:
	Square(float x, float y,const RgbColor &color);
	void Draw();
};

#endif  //_SQUARE_H
