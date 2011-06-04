#pragma once
#include "Ball.h"

class BlueBall : virtual public Ball
{
public:
	BlueBall(const float &X,const float &Y, int natuX, int natuY);
	BlueBall(){;};
	~BlueBall(void);
};
