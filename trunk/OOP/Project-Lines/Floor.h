#pragma once
#include "Cell.h"

class Floor : public Cell
{
public:
	//static std::vector <Sprite> _sprite;
	Floor(const float &X,const float &Y);
	void setFloorType(Types type);
	bool operator==(const Floor &Other)const
	{
		return(true);
	}

	bool getBalled()const
	{

		return(_balled);

	}
	void setBalled(const bool &value)
	{

		_balled = value;

	}
	//void Draw()
	//{
	//	if(_type== Simple)
	//		_sprites[0].Draw(_cordX, _cordY);
	//	else if(_type = Selected)
	//		_sprites[1].Draw(_cordX, _cordY);
	//}

	void Draw(Action action)
	{
		if(_type== Simple)
			_sprites[0].Draw(_cordX, _cordY, action);
		else if(_type = Selected)
			_sprites[1].Draw(_cordX, _cordY, action);
	} 


	~Floor(void);
private:
	bool	_balled;	//	have ball on this cell
	Types _type;
};
