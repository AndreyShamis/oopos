#pragma once
/*

	This class provide config and define variables	
*/

#define RGBA_FOLDER			"RGBA"


#define CHAR_MAX_STR_LEN    290
//balls
#define BLACK_BALL			"black_ball_rgba.txt"
#define BLUE_BALL			"blue_ball_rgba.txt"
#define GREEN_BALL			"green_ball_rgba.txt"
#define G_Y_BALL			"green_yellow_ball_rgba.txt"
#define ORANGE_BALL			"orange_ball_rgba.txt"
#define O_R_BALL			"orange_red_ball_rgba.txt"
#define RED_BALL			"red_ball_rgba.txt"
#define WHITE_BALL			"white_ball_rgba.txt"
#define W_B_BALL			"white_blue_ball_rgba.txt"
#define YELLOW_BALL			"yellow_ball_rgba.txt"
#define MIXED_BALL			"mixed_ball_rgba.txt"
#define BOMB_BALL			"bomb_rgba.txt"

//game bard
#define GAME_BOARD			"game_board_rgba.txt"
#define GAME_RULES			"rules_rgba.txt"
#define GAME_OVER			"game_over_rgba.txt"



//floor
#define FLOOR				"floor_rgba.txt"
#define S_FLOOR				"selected_floor2_rgba.txt"


#define WINDOW_WIDTH		577
#define WINDOW_HEIGHT		403

#define FLOOR_SIZE			36.0f
#define BALL_SIZE			32.0f
#define POINT_SIZE			1.0f


#define MAX_SOUNDS			7

struct Vertex
{
	float _x;
	float _y;
};

struct RGBA{					// for glut
	short int  _r, _g, _b, _a;
};

enum Types { Simple, Selected };		// floor type

enum Direction { Row, Column, BackRow, BackColumn }; // direction to find erase

enum SoundsName { Appear, Disappear, double_bonus, error, explosion,
				  BackGround};

enum BallColor { Green, White, Black, Yellow, Orange, Blue, Red , Mixed , Bomb,
				 OrangeRed, WhiteBlue, greenYellow };

