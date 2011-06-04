#pragma once
#include "GreenBall.h"
#include "YellowBall.h"

class GreenYellowBall : public GreenBall, public YellowBall
{
public:
	GreenYellowBall(const float &X,const float &Y, int natuX, int natuY);
	GreenYellowBall(){;};
	~GreenYellowBall(void);
};
