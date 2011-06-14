#include "WhiteBlueBall.h"

//=============================================================================
// Constructor
WhiteBlueBall::WhiteBlueBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(W_B_BALL);//	put the image to the sector of sprites

	//	define the colors of the ball
	_colors.push_back(White);
	_colors.push_back(Blue);

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}

//=============================================================================
// Destructor
WhiteBlueBall::~WhiteBlueBall(void)
{
}
