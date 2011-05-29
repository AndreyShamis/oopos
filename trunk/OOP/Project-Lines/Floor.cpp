#include "Floor.h"

//std::vector <Sprite> Cell::_sprite;
Floor::Floor(const float &X,const float &Y)
{
	_cordX = X;
	_cordY = Y;
	_balled = false;
	 _type = Simple;
	_sprites.push_back(FLOOR);		//	put the image to the cector of sprites
	_sprites.push_back(S_FLOOR);		//	put the image to the cector of sprites
}

Floor::~Floor(void)
{
}

void Floor::setFloorType(Types type)
{
	_type = type;
}

