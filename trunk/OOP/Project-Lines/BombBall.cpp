#include "BombBall.h"

BombBall::BombBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(BOMB_BALL);//	put the image to the cector of sprites

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}
BombBall::~BombBall(void)
{
}
