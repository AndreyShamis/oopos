#include "OrangeRedBall.h"

//=============================================================================
// Constructor
OrangeRedBall::OrangeRedBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(O_R_BALL);//	put the image to the sector of sprites

	//	define the colors of the ball
	_colors.push_back(Orange);
	_colors.push_back(Red);

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}

//=============================================================================
// Destructor
OrangeRedBall::~OrangeRedBall(void)
{
}
