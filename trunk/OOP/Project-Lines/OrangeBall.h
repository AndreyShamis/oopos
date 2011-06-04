#pragma once
#include "Ball.h"

class OrangeBall : virtual public Ball
{
public:
	OrangeBall(const float &X,const float &Y, int natuX, int natuY);
	OrangeBall(){;};
	~OrangeBall(void);
};
