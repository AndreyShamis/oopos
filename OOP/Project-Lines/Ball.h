#pragma once
#include "Cell.h"
class Ball : public Cell
{
public:
	Ball(const float &X,const float &Y, BallColor color);
	//void Draw();
	void Draw(Action action);
	bool Ball::doYouThatColor(BallColor color);
	~Ball(void);
	bool operator==(const Ball &Other)const
	{
		return(true);
	}
private:

	vector <BallColor> _colors;

};
