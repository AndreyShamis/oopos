#pragma once
#include "Ball.h"

class YellowBall : virtual public Ball
{
public:
	YellowBall(const float &X,const float &Y, int natuX, int natuY);
	YellowBall(){;};
	~YellowBall(void);
};
