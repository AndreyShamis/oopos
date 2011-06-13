#pragma once
#include "macros.h"
#include "Drawable.h"


class Ball : public Drawable
{
public:
	//virtual Ball(const float &X,const float &Y, int natuX, int natuY)=0;
	bool operator==(const Ball &other)const;
	void Draw();
	bool doYouABomb()const;
	Ball();
	~Ball(void);
	void setSelected();
	void unSelect();
	void mustDie();
	void mustBorn();
protected:


	bool _selected;
	bool _bombExist;
	vector <BallColor> _colors;

};
