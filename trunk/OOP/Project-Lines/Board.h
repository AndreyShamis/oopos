#pragma once
#include "Cell.h"

class Board : public Cell
{
public:
	Board(const float &X,const float &Y);
	void Draw();
	~Board(void);
};  
