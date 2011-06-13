#include "Board.h"

//=============================================================================
//
Board::Board(const float &X,const float &Y)
{
	_cordX = X;
	_cordY = Y;
	_sprites.push_back(GAME_BOARD);	
	_sprites.push_back(GAME_RULES);
	_sprites.push_back(GAME_OVER);
}
	
//=============================================================================
//
Board::~Board(void)
{
}
//=============================================================================
//
void Board::Draw()
{
		_sprites[0].Draw(_cordX, _cordY);
}

