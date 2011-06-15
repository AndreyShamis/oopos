#pragma once
#include "macros.h"
#include "Dragable.h"

class Ball :virtual public Dragable
{
public:
	Ball();
	~Ball();
	void Draw();
	bool doYouABomb()const;
	void setSelected();
	void unSelect();
	void mustDie();
	void mustBorn();
	bool operator==(const Ball &other)const;
protected:
	bool _selected;
	bool _bombExist;
	vector <BallColor> _colors;
};
