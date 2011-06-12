#include "Ball.h"
/*

Ball::Ball(const float &X,const float &Y, int natuX, int natuY)
{
	_cordX = X;
	_cordY = Y;
	_natuX = natuX;
	_natuY = natuY;
	
	cout << "Ball constructor\n";
}
*/
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
	if(_mustDie)
	{
		_sprites[0].unSelect();
		_selected = false;
		_sprites[0].StartTurnOff();
	}

	glEnable(GL_BLEND);									//	Alpha manipulation
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//	Alpha manipulation
	_sprites[0].Draw(_cordX+b_offset*3, b_cord_Y);
	glDisable(GL_BLEND);								//	Alpha manipulation

	if(_selected)
	{
		_sprites[0].unSelect();
		unSelect();

	}
}

bool Ball::operator==(const Ball &other)const
{
	vector<BallColor>::const_iterator itThis = _colors.begin(),
									  itOther = other._colors.begin();
				
	for(;itThis != _colors.end(); ++itThis)
	{
		for(;itOther != other._colors.end(); ++itOther)
		{
			if(*itThis == *itOther)
			{
				return true;
			}
		}
	}
	return false;
}