#pragma once
#include "WhiteBall.h"
#include "GreenBall.h"
#include "BlackBall.h"
#include "YellowBall.h"
#include "OrangeBall.h"
#include "BlueBall.h"
#include "RedBall.h"



class BombBall :	public WhiteBall, public GreenBall, public BlackBall, 
					public YellowBall, public OrangeBall, public BlueBall,
					public RedBall
{
public:
	BombBall(const float &X,const float &Y, int natuX, int natuY);
	BombBall(){;};
	~BombBall();
};
