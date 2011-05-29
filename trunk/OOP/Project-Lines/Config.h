/*

	This class provide config and define variables	
*/

#define RGBA_FOLDER			"RGBA"


#define CHAR_MAX_STR_LEN    200
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



//
//
//
//
//#define MENU_USR_L_1		"player_score_1_rgba.txt"
//#define MENU_USR_L_2		"player_score_2_rgba.txt"
//#define MENU_USR_L_3		"player_score_3_rgba.txt"
//
//#define MENU_ENM_L_1		"enemy_score_1_rgba.txt"
//#define MENU_ENM_L_2		"enemy_score_2_rgba.txt"
//#define MENU_ENM_L_3		"enemy_score_3_rgba.txt"
//
//
//#define SPACE				"space_rgba.txt"
//#define SURPRISE			"surprise_rgba.txt"
//#define WALL				"brich_wall_rgba.txt"
//#define ENEMY_D				"enemy.down_rgba.txt"
//#define ENEMY_L				"enemy.left_rgba.txt"
//#define ENEMY_R				"enemy.right_rgba.txt"
//#define ENEMY_U				"enemy.up_rgba.txt"
//#define PLAYER_D			"Player.down_rgba.txt"
//#define PLAYER_L			"Player.left_rgba.txt"
//#define PLAYER_R			"Player.right_rgba.txt"
//#define PLAYER_U			"Player.up_rgba.txt"
//#define EXP_VER				"explosion_vertical_rgba.txt"
//#define EXP_UP				"explosion_up_rgba.txt"
//#define EXP_START			"explosion_start_rgba.txt"
//#define EXP_RIGHT			"explosion_right_rgba.txt"
//#define EXP_LEFT			"explosion_left_rgba.txt"
//#define EXP_HOR				"explosion_horizontal_rgba.txt"
//#define EXP_DOWN			"explosion_down_rgba.txt"
//#define EXP_VER_USR			"explosion_vertical_user_rgba.txt"
//#define EXP_UP_USR			"explosion_up_user_rgba.txt"
//#define EXP_START_USR		"explosion_start_user_rgba.txt"
//#define EXP_DOWN_USR		"explosion_down_user_rgba.txt"
//#define EXP_RIGHT_USR		"explosion_right_user_rgba.txt"
//#define EXP_LEFT_USR		"explosion_left_user_rgba.txt"
//#define EXP_HOR_USR			"explosion_horizontal_user_rgba.txt"
//#define BOMB_BEFOR			"bomb.one.step.befor.explogen_rgba.txt"
//#define BOMB_STEP_ONE		"bomb_step_one_rgba.txt"
//#define BOMB_STEP_TWO		"bomb_step_two_rgba.txt"
//
//#define BOMB_STEP_TWO_USR	"bomb_step_two_user_rgba.txt"
//#define BOMB_STEP_ONE_USR	"bomb_step_one_user_rgba.txt"
//#define BOMB_BEFOR_USR		"bomb.one.step.befor.explosion.user_rgba.txt"

//
//#define STEP_SPEED 7
//
#define PIC_WIDTH 33
//
//#define LEFT_KEY			'4'
//#define RIGHT_KEY			'6'
//#define TOP_KEY				'8'
//#define DOWN_KEY			'2'
//#define BOMB_KEY_B			'b'
//#define BOMP_KEY_S			' '
//
//#define EXIT_KEY			'q'
//#define RELOAD_GAME			'n'
//
//#define FIRE_SIZE			4

struct Vertex
{
	float _x;
	float _y;
};

struct RGBA{
	short int  _r, _g, _b, _a;
};

enum Types { Simple, Selected };
enum Action { Nothing, Appear, Disappear };

enum BallColor { Green, White, Black, Yellow, Orange, Blue, Red , Mixed , 
				 OrangeRed, WhiteBlue, greenYellow };