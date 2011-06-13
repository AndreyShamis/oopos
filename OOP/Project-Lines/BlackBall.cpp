#include "BlackBall.h"

BlackBall::BlackBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(BLACK_BALL);//	put the image to the sector of sprites

	_colors.push_back(Black);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
	_mulColor = false;
}


BlackBall::~BlackBall(void)
{
}
