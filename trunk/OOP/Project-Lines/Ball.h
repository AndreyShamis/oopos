#pragma once
#include "Drawable.h"

class Ball : public Drawable
{
public:
	Ball(const float &X,const float &Y, int natuX, int natuY);
	void Draw();
	Ball(){;};
	//Ball(const float &X,const float &Y, int natuX, int natuY);
	//void Draw();




	//bool Ball::doYouThatColor(BallColor color);
	~Ball(void);
	// Ball(void)
	// {

	//	 ;
	// }
private:

	vector <BallColor> _colors;

};
