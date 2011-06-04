#pragma once
#include "Ball.h"

class WhiteBall : virtual public Ball
{
public:
	WhiteBall(const float &X,const float &Y, int natuX, int natuY);
	WhiteBall(){;};
	~WhiteBall(void);
};
