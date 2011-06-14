#include "MixedBall.h"

//=============================================================================
// Constructor
MixedBall::MixedBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(MIXED_BALL);//	put the image to the cector of sprites

	//	define the colors of the ball
	_colors.push_back(Blue);
	_colors.push_back(Yellow);
	_colors.push_back(White);
	_colors.push_back(Orange);
	_colors.push_back(Black);
	_colors.push_back(Red);
	_colors.push_back(Green);

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
	
}
//=============================================================================
// Destructor
MixedBall::~MixedBall(void)
{
}
