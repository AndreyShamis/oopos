#include "Ball.h"

Ball::Ball(const float &X,const float &Y, BallColor color)
{
	switch(color){

		case Green:			_sprites.push_back(GREEN_BALL);		//	put the image to the cector of sprites
							_colors.push_back(color);	
							break;
		case White:			_sprites.push_back(WHITE_BALL);
							_colors.push_back(color);	
							break;
		case Black:			_sprites.push_back(BLACK_BALL);
							_colors.push_back(color);	
							break;
		case Yellow:		_sprites.push_back(YELLOW_BALL);
							_colors.push_back(color);
							break;
		case Orange:		_sprites.push_back(ORANGE_BALL);
							_colors.push_back(color);
							break;
		case Red:			_sprites.push_back(RED_BALL);
							_colors.push_back(color);
							break;
		case Blue:			_sprites.push_back(BLUE_BALL);
							_colors.push_back(color);
							break;
		case OrangeRed:		_sprites.push_back(O_R_BALL);
							_colors.push_back(Orange);
							_colors.push_back(Red);
							break;
		case WhiteBlue:		_sprites.push_back(W_B_BALL);
							_colors.push_back(White);
							_colors.push_back(Blue);
							break;
		case greenYellow:	_sprites.push_back(G_Y_BALL);
							_colors.push_back(Green);
							_colors.push_back(Yellow);
							break;
		case Mixed:			_sprites.push_back(MIXED_BALL);
							_colors.push_back(Green);
							_colors.push_back(White);
							_colors.push_back(Black);
							_colors.push_back(Yellow);
							_colors.push_back(Orange);
							_colors.push_back(Red);
							_colors.push_back(Blue);
							break;
	}
	float b_offset = ((FLOOR_SIZE - BALL_SIZE)/2)/WINDOW_WIDTH;
	_cordX = X+b_offset*3;
	_cordY = Y+b_offset;
}

bool Ball::doYouThatColor(BallColor color)
{
	// loop vector colors and if colors matched return true.
	for(vector<BallColor>::const_iterator it = _colors.begin();
		it != _colors.end(); ++it)
	{
		if(*it == color)
			return true;
	}
	return false;
}

//void Ball::Draw()
//{
//	_sprites[0].Draw(_cordX, _cordY);
//}
 
Ball::~Ball(void)
{
}

void Ball::Draw()
{
	_sprites[0].Draw(_cordX, _cordY);
}