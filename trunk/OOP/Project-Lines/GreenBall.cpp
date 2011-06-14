#include "GreenBall.h"

//=============================================================================
// Constructor
GreenBall::GreenBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(GREEN_BALL);//	put the image to the sector of sprites

	_colors.push_back(Green);		//	define the colors of the ball

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}
//=============================================================================
// Destructor
GreenBall::~GreenBall(void)
{
}
