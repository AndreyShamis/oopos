#include "BombBall.h"

BombBall::BombBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(BOMB_BALL);//	put the image to the cector of sprites

	_colors.push_back(Blue);
	_colors.push_back(Yellow);
	_colors.push_back(White);
	_colors.push_back(Orange);
	_colors.push_back(Black);
	_colors.push_back(Red);
	_colors.push_back(Green);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}
BombBall::~BombBall(void)
{
}
