#pragma once
#include "Drawable.h"

class Board : public Drawable
{
public:
	Board(const float &X,const float &Y);
	void Draw();
	~Board(void);

	void setShowMode(const short int val)
	{
		_showMode = val;
	}
private:
	short int _showMode;

};  
