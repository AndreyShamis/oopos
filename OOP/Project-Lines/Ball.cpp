#include "Ball.h"


Ball::Ball(const float &X,const float &Y, int natuX, int natuY)
{
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
	_selected = false;
}

Ball::~Ball(void)
{
}

void Ball::Draw()
{
	float b_offset = ((FLOOR_SIZE - BALL_SIZE)/2)/WINDOW_WIDTH;
	float b_cord_Y = _cordY + b_offset;
	if(_selected)
	{
		_sprites[0].setSelected();

	}
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_sprites[0].Draw(_cordX+b_offset*3, b_cord_Y);
	glDisable(GL_BLEND);

	if(_selected)
	{
		_sprites[0].unSelect();
		unSelect();

	}
}



//bool Ball::doYouThatColor(BallColor color)
//{
//	// loop vector colors and if colors matched return true.
//	for(vector<BallColor>::const_iterator it = _colors.begin();
//		it != _colors.end(); ++it)
//	{
//		if(*it == color)
//			return true;
//	}
//	return false;
//}

// loop vector colors and if colors matched return true.




bool Ball::operator==(const Ball &other)const
{
	for(vector<BallColor>::const_iterator itThis = this->_colors.begin();
		itThis != _colors.end(); ++itThis)
	{
		for(vector<BallColor>::const_iterator itOther = other._colors.begin();
			itOther != _colors.end(); ++itOther)
		{
			if(*itThis == *itOther)
				return true;
		}
	}
	return false;
}