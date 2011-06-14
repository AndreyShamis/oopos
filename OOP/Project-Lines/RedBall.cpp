#include "RedBall.h"

//=============================================================================
// Constructor
RedBall::RedBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(RED_BALL);//	put the image to the sector of sprites

	_colors.push_back(Red);		//	define the colors of the ball

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}
//=============================================================================
// Destructor
RedBall::~RedBall(void)
{
}
