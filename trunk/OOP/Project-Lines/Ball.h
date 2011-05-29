#pragma once
#include "Cell.h"
class Ball : public Cell
{
public:
	Ball(BallColor color);
	~Ball(void);

private:

	vector <BallColor> _colors;

};
