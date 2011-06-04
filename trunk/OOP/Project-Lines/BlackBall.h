#pragma once
#include "Ball.h"

class BlackBall : virtual public Ball
{
public:
	BlackBall(const float &X,const float &Y, int natuX, int natuY);
	BlackBall(){;};
	~BlackBall(void);
};
