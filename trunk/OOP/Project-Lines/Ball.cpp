#include "Ball.h"

//=============================================================================
//			Constructor
Ball::Ball()
{
	_bombExist = false;		//	Have bomb
	_selected = true;		//	Set be selected by default
}
//=============================================================================
//			Destructor
Ball::~Ball()
{
}
//=============================================================================
//			Selected
void Ball::setSelected()
{
	_selected = true;
}
//=============================================================================
//			Unselect
void Ball::unSelect()
{
	_selected = false;
}
//=============================================================================
//			Set must be removed from game
void Ball::mustDie()
{
	_sprites[0].StartTurnOff();
}
//=============================================================================
//			Set must be added to board
void Ball::mustBorn()
{
	_sprites[0].StartTurnOn();
}
//=============================================================================
//			Function Wich call to sprite draw
void Ball::Draw()
{
	float b_offset = ((FLOOR_SIZE - BALL_SIZE)/2)/WINDOW_WIDTH;
	float b_cord_Y = _cordY + b_offset;

	if(_selected)					//	if ball selected
		_sprites[0].setSelected();	//	set sprite alpha

	glEnable(GL_BLEND);									//	Alpha manipulation
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//	Alpha manipulation
	_sprites[0].Draw(_cordX+b_offset*3, b_cord_Y);		//	Draw ball
	glDisable(GL_BLEND);								//	Alpha manipulation

	if(_selected)					//	remove selection
	{
		_sprites[0].unSelect();		//	unselect
		unSelect();					//	unselect self

	}
}
//=============================================================================
//			Compare between colors
bool Ball::operator==(const Ball &other)const
{
	//	Get two iterators
	vector<BallColor>::const_iterator itThis = _colors.begin(),
									  itOther = other._colors.begin();
				
	for(itThis = _colors.begin();itThis != _colors.end(); itThis++)
	{
		for(itOther=other._colors.begin();itOther != other._colors.end();itOther++)
		{
			if(*itThis == *itOther)		//	compare having
				return (true);			//	return true if found
		}
	}
	return (false);						//	not found
}	
//=============================================================================
//			For ask object if the object is bomb
bool Ball::doYouABomb()const
{
	return(_bombExist);
}


