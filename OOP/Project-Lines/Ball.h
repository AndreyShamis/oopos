#pragma once
#include "Cell.h"

class Ball : public Cell
{
public:
	Ball(const float &X,const float &Y, BallColor color);
	void Draw();
	bool Ball::doYouThatColor(BallColor color);
	~Ball(void);

private:

	vector <BallColor> _colors;

};
