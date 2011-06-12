#include "BlueBall.h"

BlueBall::BlueBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(BLUE_BALL);//	put the image to the sector of sprites

	_colors.push_back(Blue);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}


BlueBall::~BlueBall(void)
{
}
