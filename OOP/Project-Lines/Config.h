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

//game bard
#define GAME_BOARD			"game_board_rgba.txt"


//floor
#define FLOOR				"floor_rgba.txt"
#define S_FLOOR				"selected_floor_rgba.txt"


struct Vertex
{
	float _x;
	float _y;
};

struct RGBA{
	short int  _r, _g, _b, _a;
};

enum Types { Simple, Selected };

enum BallColor { Green, White, Black, Yellow, Orange, Blue, Red , Mixed , 
				 OrangeRed, WhiteBlue, greenYellow };