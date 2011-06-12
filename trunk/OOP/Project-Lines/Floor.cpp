#include "Floor.h"

//std::vector <Sprite> Cell::_sprite;
Floor::Floor()
{
/*	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;*/
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


void Floor::Draw()
{
	if(_type== Simple)
		_sprites[0].Draw(_cordX, _cordY);
	else if(_type = Selected)
		_sprites[1].Draw(_cordX, _cordY);
} 

void Floor::setBalled(const bool &value)
{
	_balled = value;
}

bool Floor::getBalled()const
{
	return(_balled);
}