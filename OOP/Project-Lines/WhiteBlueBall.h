#pragma once
#include "WhiteBall.h"
#include "BlueBall.h"

class WhiteBlueBall : public WhiteBall, public BlueBall
{
public:
	WhiteBlueBall(const float &X,const float &Y, int natuX, int natuY);
	WhiteBlueBall(){;};
	~WhiteBlueBall(void);
};
