#pragma once
#include "Ball.h"

class RedBall : virtual public Ball
{
public:
	RedBall(const float &X,const float &Y, int natuX, int natuY);
	RedBall(){cout << "GGGGGGGGGGGG\n";};
	~RedBall(void);
};
