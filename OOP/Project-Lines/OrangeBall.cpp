#include "OrangeBall.h"

OrangeBall::OrangeBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(ORANGE_BALL);//	put the image to the sector of sprites

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}


OrangeBall::~OrangeBall(void)
{
}
