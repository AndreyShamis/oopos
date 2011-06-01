#pragma once
#include "Cell.h"

class Floor : public Cell
{
public:
	//static std::vector <Sprite> _sprite;
	Floor(const float &X,const float &Y);
	void setFloorType(Types type);
	bool getBalled()const;
	void setBalled(const bool &value);
	void Draw();
	~Floor(void);
private:
	bool	_balled;	//	have ball on this cell
	Types _type;
};
