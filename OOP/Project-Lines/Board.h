#pragma once
#include "Drawable.h"

class Board : public Drawable
{
public:
	Board(const float &X,const float &Y);
	void Draw();
	~Board(void);
};  
