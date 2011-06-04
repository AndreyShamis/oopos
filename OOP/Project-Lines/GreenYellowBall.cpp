#include "GreenYellowBall.h"

GreenYellowBall::GreenYellowBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(G_Y_BALL);//	put the image to the cector of sprites

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}


GreenYellowBall::~GreenYellowBall(void)
{
}
