#pragma once
#include "Drawable.h"

class Floor : public Drawable
{
public:
	//static std::vector <Sprite> _sprite;
	Floor(const float &X,const float &Y, int natuX, int natuY);
	//Floor(){1,1,-1,-1;};
	void setFloorType(Types type);
	bool getBalled()const;
	void setBalled(const bool &value);
	void Draw();
	~Floor(void);
private:
	bool	_balled;	//	have ball on this cell
	Types _type;
};
