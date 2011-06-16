#pragma once

#include "Graph.h"
#include "Sprite.h"
#include "Floor.h"
#include "Drawable.h"
#include "Ball.h"
#include "Board.h"
#include "macros.h"
#include <math.h>
#include "BombBall.h"
#include "OrangeRedBall.h"
#include "WhiteBlueBall.h"
#include "MixedBall.h"
#include "GreenYellowBall.h"


#include <fmod.h>
#include <fmod.hpp>
#include <windows.h>
#include "resource.h"

#include <map>
using namespace std;





//IDR_PROJECTLINES1;    

#define _EASY_REDISPLAY 10000
#define _FAST_REDISPLAY 100
#define _BOARD_SIZE_X 9
#define _BOARD_SIZE_Y 9
#define _BOARD_SIZE 9
#define _H_BOARD_SIZE 4

//	game status
#define _STATUS_GAME_OFF 1
#define _STATUS_GAME_ON 2
#define _STATUS_GAME_END 3
#define _STATUS_GAME_SHOW_HELP 4

//	pos floor
#define _POS_FLOOR_X_START 0.2025
#define _POS_FLOOR_Y_START 0.063

#define _POINT_CHAR_SIZE 10

#define _BALLS_MAX_SIZE_PER_PUTING 3
#define _POS_BALL_X_START 0.8225
#define _POS_BALL_Y_START 0.183
#define _POS_BALL_Y_OFFSET 0.1

#define _KEY_NEW_GAME 'n'
#define _KEY_EXIT_GAME 'q'
#define _KEY_HELP 'h'
#define _KEY_HELP_EXIT 'g'

#define _MNU_KEY_NEW_GAME 1
#define _MNU_KEY_EXIT_GAME 2
#define _MNU_KEY_HELP 3
#define _MNU_KEY_HELP_EXIT 4
#define _MNU_KEY_GAME_OVER 5

#define _MAX_POST_REDISPLAY_VEC_SIZE 25
#define _MIN_POST_REDISPLAY_VEC_SIZE 15
struct Ball_Postion
{
	int x;
	int y;
	bool operator<(const Ball_Postion &val)const
	{
		return(val.x < this->x ||((val.x == this->x) && val.y < this->y));
	}

};

//#define _MAP_KEY_IS_VECint 1	//	For use vector such key
//#define _MAP_KEY vector<int>	//	For use vector such key

#define _MAP_KEY_IS_STRUCT 1	//	For use sruct such key
#define _MAP_KEY Ball_Postion	//	For use sruct such key


class GameController
{
	// all the documentation of functions are located at cpp file
public:
	static GameController *getInst();	
	static void mouseButton(int button, int state, int x, int y);
	static void mouseMove(int x, int y);
	static void selectFromMenu(int commandId);
	static void resizeWindow(int w, int h);
	static void LoadCallBacksForGlut();
	static void LoadGame();
	static void idle();
	static void display();
	static void KeyPress(unsigned char key, int x, int y);
	static void CreateMenuForGlut();
	static void Menu(const int val);
private:
	GameController();
	static bool CheckColsRowsFix(const int start,const int end, const int rowCol,Direction direc);

	static void GarbageColector();
	static void glutPrint(float x, float y, char* text, float r, float g,
														float b, float a);
	static int FindFloorByCord(const float &xPos ,const float &yPos);
	static void MouseUp();
	static void PrepareSimplePath();
	static void RealodGame();
	static void loadSounds();
	static void printErrorMSG(char *sentence);
	static void playSound(SoundsName soundName);
	static void setKey(const int &coordX, const int &coordY);
	static void loadBalls();
	static void loadFloors();
	static void CreateBall();
	static void PutBall();
	static void BumBum();
	static void checkRowsAndCols();
	static void checkDiagonals();
	static void FloorDoAllSimple();
	static void BumAroundBomb(const short int &_x,const short int &_y);
	static void scanDiagonal(const short int &i, Direction direc);
	static void scanRowCol(const short int &i, Direction direc);
	static bool ballsComp(map<_MAP_KEY,Ball>::const_iterator &b1,
						  map<_MAP_KEY,Ball>::const_iterator &b2);

	static int				GameStatus;		// Game status/loaded/unloaded/etc
	static Graph<Floor>		_floors;		//	Graph of cells
	static int				_WindowHeight;	//	Window
	static int				_WindowWidth;	//	Window
	static GameController	*_instance;		//	Singleton
	static Board			gameBoard;		//	Game board Background
	static vector <Ball>	_newBalls;		//	ProGame vector of balls
	static vector <Ball>	_postBalls;		//	PostGame vector of balls
	static vector <BallColor> _AllColors;	//	Color of balls
	static FMOD::Sound*		_sounds[MAX_SOUNDS];	//	Saund variable
	static unsigned int		_StartCell;		//	ID of ball for simple path
	static unsigned int		_EndCell;		//	ID of floor for simple path
	static FMOD::System*	_system;		//	Sound system
	static _MAP_KEY			_coords;		//	To know wich ball we want	
	static map<_MAP_KEY ,Ball>	_BallMap;	//	the balls data base (STL)
	static vector <Ball>	_Balls;			//	all colors balls for copy
	static bool				_BallEraseBoard[_BOARD_SIZE_X][_BOARD_SIZE_Y];
	static bool				_canAddBalls;	//	Value to know if need put new 
											//	ball
	static int				_BallCounter;	//	Counter of balls on board
	static int				PrevFounded;	//	To know if in previous move 
											//	user found combination
	static int				GamePoints;		//	Points of Game
	static unsigned int		_PostRedisplay;	//	Counter for redisplay
	static bool				_bombExist;		//  bomb existence

};
