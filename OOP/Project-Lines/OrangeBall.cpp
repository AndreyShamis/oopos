#include "OrangeBall.h"

//=============================================================================
// Constructor
OrangeBall::OrangeBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(ORANGE_BALL);//	put the image to the sector of sprites

	_colors.push_back(Orange);		//	define the colors of the ball

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}

//=============================================================================
// Destructor
OrangeBall::~OrangeBall(void)
{
}
