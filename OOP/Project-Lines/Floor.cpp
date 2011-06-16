#include "Floor.h"

//=============================================================================
// Constructor
Floor::Floor()
{
	_balled = false;
	 _type = Simple;
	_sprites.push_back(FLOOR);		//	put the image to the cector of sprites
	_sprites.push_back(S_FLOOR);	//	put the image to the cector of sprites
}
//=============================================================================
// Destructor
Floor::~Floor(void)
{
}
//=============================================================================
//	Function used for selecting floor type
void Floor::setFloorType(Types type)
{
	_type = type;
}

//=============================================================================
//	Function wich draw the floor
void Floor::Draw()
{
	if(_type== Simple)
		_sprites[0].Draw(_cordX, _cordY);
	else if(_type = Selected)
		_sprites[1].Draw(_cordX, _cordY);
} 
//=============================================================================
//
void Floor::setBalled(const bool &value)
{
	_balled = value;
}
//=============================================================================
//
bool Floor::getBalled()const
{
	return(_balled);
}