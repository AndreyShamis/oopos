#pragma once
#include "Cell.h"

class Floor : public Cell
{
public:
	static std::vector <Sprite> _sprite;
	Floor(const float &X,const float &Y);
	void setFloorType(FloorType type);
	bool operator==(const Floor &Other)const
	{
		return(true);
	}
	void Draw()
	{
		if(_type== Simple)
			_sprite[0].Draw(_cordX, _cordY);
		else if(_type = Selected)
			_sprite[1].Draw(_cordX, _cordY);
	}
	~Floor(void);
private:

	FloorType _type;
};
