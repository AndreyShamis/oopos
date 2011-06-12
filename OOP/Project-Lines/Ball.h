#pragma once
#include "macros.h"
#include "Drawable.h"


class Ball : public Drawable
{
public:
	Ball(const float &X,const float &Y, int natuX, int natuY);
	bool operator==(const Ball &other)const;
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

	void setSelected()
	{
		_selected = true;

	}
	void unSelect()
	{
		_selected = false;
	}
protected:


	bool _selected;
	vector <BallColor> _colors;

};
