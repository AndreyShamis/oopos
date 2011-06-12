#include "Graph.h"
#include "Sprite.h"
#include "Floor.h"
#include "Drawable.h"
#include "Ball.h"
#include "Board.h"
#include "macros.h"


#include "BombBall.h"
#include "OrangeRedBall.h"
#include "WhiteBlueBall.h"
#include "MixedBall.h"
#include "GreenYellowBall.h"

#include <map>
#include <fmod.h>
#include <fmod.hpp>
#include <windows.h>

#pragma once
using namespace std;

#define _BOARD_SIZE_X 9
#define _BOARD_SIZE_Y 9


class GameController
{

//friend 

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
	
private:
	static Graph<Floor>		_floors;
	static void loadSounds();
	static void printErrorMSG(char *sentence);
	static void playSound(SoundsName soundName);
	static void setVecOfCoords(const int &coordX, const int &coordY);
	static void loadBalls();
	static void loadFloors();

	static void BumBum();
	static void checkRowsAndCols();
	static void checkDiagonals();
	static void updDiagonLftDownExis(const short int &i, Direction direc);


	static void updateLineExistence(const short int &i,
									short int &matchCounter,
									short int &start,Direction direc);

	static void updateBallEraseBoard(const short int &location,
									 const short int &matchCounter,
									 const short int &start,
									 Direction direc);


	static bool ballsComp(map<vector<int>,Ball>::const_iterator &b1,
						  map<vector<int>,Ball>::const_iterator &b2);



	static void RealodGame();
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	static Board gameBoard;
	static void CreateBall();
	static void PutBall();
	//static vector <Ball>  _ballsMap;
	static vector <Ball> _newBalls;
	static vector <BallColor> _AllColors;
	static FMOD::Sound* _sounds[MAX_SOUNDS];
	
	static unsigned int _StartCell;
	static unsigned int _EndCell;
	static FMOD::System* _system;		// Sound system
	static vector <int> _coords;

	static map<vector<int> ,Ball>	_BallMap;			// the balls data base (STL)


	static vector <Ball> _Balls;

	static bool _BallEraseBoard[_BOARD_SIZE_X][_BOARD_SIZE_Y];


	static bool _canAddBalls;
	GameController();

	static int _BallCounter;
	static void FloorDoAllSimple();

	
	static int PrevFounded;
	static int GamePoints;
	static unsigned int _PostRedisplay;

	static void glutPrint(float x, float y, char* text, float r, float g, float b, float a);
};
