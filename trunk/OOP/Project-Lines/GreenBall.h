#pragma once
#include "ball.h"

class GreenBall : virtual public Ball
{
public:
	GreenBall(const float &X,const float &Y, int natuX, int natuY);
	GreenBall(){;};
	~GreenBall(void);
};
