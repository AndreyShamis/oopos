#pragma once
#include "Dragable.h"

class Floor :virtual public Dragable
{
public:
	Floor();
	void setFloorType(Types type);
	bool getBalled()const;
	void setBalled(const bool &value);
	void Draw();
	~Floor(void);
private:
	bool	_balled;	//	have ball on this cell
	Types _type;
};
