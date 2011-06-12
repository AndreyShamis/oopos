#pragma once
#include "macros.h"
#include "Drawable.h"


class Ball : public Drawable
{
public:
	//virtual Ball(const float &X,const float &Y, int natuX, int natuY)=0;
	bool operator==(const Ball &other)const;
	void Draw();
	Ball()
	{
		_selected = true;
		_mustDie = false;
	}
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

	void mustDie()
	{
		_mustDie = true;
		_sprites[0].StartTurnOff();
	}
protected:


	bool _selected;
	bool _mustDie;
	vector <BallColor> _colors;

};
