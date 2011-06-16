#pragma once
#include "Drawable.h"

class Board : public Drawable
{
public:
	Board(const float &X,const float &Y);
	void Draw();
	void setShowMode(const short int val);
	~Board(void);
private:
	short int _showMode;

};  
