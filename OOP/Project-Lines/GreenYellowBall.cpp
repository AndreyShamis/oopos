#include "GreenYellowBall.h"

//=============================================================================
// Constructor
GreenYellowBall::GreenYellowBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(G_Y_BALL);//	put the image to the cector of sprites

	//	define the colors of the ball
	_colors.push_back(Yellow);
	_colors.push_back(Green);

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}

//=============================================================================
// Destructor
GreenYellowBall::~GreenYellowBall(void)
{
}
