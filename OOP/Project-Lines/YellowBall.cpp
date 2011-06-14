#include "YellowBall.h"

//=============================================================================
// Constructor
YellowBall::YellowBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(YELLOW_BALL);//	put the image to the vector of sprites

	_colors.push_back(Yellow);		//	define the colors of the ball

	// set real and natural coords
	_cordX = X;						
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}
//=============================================================================
// Destructor
YellowBall::~YellowBall(void)
{
}
