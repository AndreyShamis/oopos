#include "OrangeRedBall.h"

OrangeRedBall::OrangeRedBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(O_R_BALL);//	put the image to the sector of sprites

	_colors.push_back(Orange);
	_colors.push_back(Red);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}


OrangeRedBall::~OrangeRedBall(void)
{
}