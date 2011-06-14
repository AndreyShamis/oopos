#include "BlueBall.h"

//=============================================================================
// Constructor
BlueBall::BlueBall(const float &X,const float &Y, int natuX, int natuY)
{
	_sprites.push_back(BLUE_BALL);//	put the image to the sector of sprites

	_colors.push_back(Blue);	  //	define the colors of the ball

	// set real and natural coords
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
}

//=============================================================================
// Destructor
BlueBall::~BlueBall(void)
{
}
