#include "WhiteBall.h"

//=============================================================================
//
WhiteBall::WhiteBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(WHITE_BALL);//	put the image to the sector of sprites

	_colors.push_back(White);

	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}

//=============================================================================
//
WhiteBall::~WhiteBall(void)
{
}
