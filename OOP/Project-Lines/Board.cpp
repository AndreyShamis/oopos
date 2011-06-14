#include "Board.h"

//=============================================================================
// Constructor
Board::Board(const float &X,const float &Y)
{
	// set coords
	_cordX = X;
	_cordY = Y;
	_showMode = 0;
	//	put the images to the vector of sprites
	_sprites.push_back(GAME_BOARD);	
	_sprites.push_back(GAME_RULES);
	_sprites.push_back(GAME_OVER);
}
	
//=============================================================================
// Destructor
Board::~Board(void)
{
}
//=============================================================================
// Function that draw sprite 
void Board::Draw()
{
		_sprites[_showMode].Draw(_cordX, _cordY);
}

