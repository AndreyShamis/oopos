#include "RedBall.h"

RedBall::RedBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(RED_BALL);//	put the image to the sector of sprites

	_colors.push_back(Red);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
	_mulColor = false;
}

RedBall::~RedBall(void)
{
}
