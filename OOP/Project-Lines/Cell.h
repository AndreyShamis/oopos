#pragma once
#include "Sprite.h"
#include "Graph.h"
//#include "Config.h"

class Cell
{
public:
	bool operator==(const Cell &Other)const
	{
		return(true);
	}
	float getX()const
	{

		return(_cordX);
	}
	float getY()const
	{

		return(_cordY);
	}
protected:
	std::vector <Sprite> _sprites;

	float _cordX;
	float _cordY;

};
