#pragma once
#include "OrangeBall.h"
#include "RedBall.h"

class OrangeRedBall : public OrangeBall, public RedBall
{
public:
	OrangeRedBall(const float &X,const float &Y, int natuX, int natuY);
	OrangeRedBall(){;};
	~OrangeRedBall(void);
};
