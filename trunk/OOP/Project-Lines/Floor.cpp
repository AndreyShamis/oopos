#include "Floor.h"

std::vector <Sprite> Floor::_sprite;
Floor::Floor(const float &X,const float &Y)
{
	_cordX = X;
	_cordY = Y;
	 _type = Simple;
	_sprite.push_back(FLOOR);		//	put the image to the cector of sprites
	_sprite.push_back(S_FLOOR);		//	put the image to the cector of sprites
}

Floor::~Floor(void)
{
}

void Floor::setFloorType(FloorType type)
{
	_type = type;
}
