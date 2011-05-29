#pragma once
#include "Sprite.h"
#include "Graph.h"
//#include "Config.h"

class Cell
{
public:
	float getX()const
	{

		return(_cordX);
	}
	float getY()const
	{

		return(_cordY);
	}
protected:
	static Graph<Sprite> _sprites;

	float _cordX;
	float _cordY;

};
