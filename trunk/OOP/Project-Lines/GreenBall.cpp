#include "GreenBall.h"

GreenBall::GreenBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(GREEN_BALL);//	put the image to the sector of sprites

	_colors.push_back(Green);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
	_mulColor = false;
}

GreenBall::~GreenBall(void)
{
}
