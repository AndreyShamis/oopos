#include "WhiteBlueBall.h"

WhiteBlueBall::WhiteBlueBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(W_B_BALL);//	put the image to the sector of sprites

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}


WhiteBlueBall::~WhiteBlueBall(void)
{
}
