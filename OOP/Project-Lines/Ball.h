#pragma once
#include "macros.h"
#include "Drawable.h"


class Ball : public Drawable
{
public:
	//virtual Ball(const float &X,const float &Y, int natuX, int natuY)=0;
	bool operator==(const Ball &other)const;
	void Draw();
	bool doYouABall()const;
	Ball()
	{
		_bombExist = false;
		_selected = true;

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
		_sprites[0].StartTurnOff();
	}
	void mustBorn()
	{
		_sprites[0].StartTurnOn();
	}
protected:


	bool _selected;
	bool _bombExist;
	vector <BallColor> _colors;

};
