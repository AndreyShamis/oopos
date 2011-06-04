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

class GameController
{
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

	static void RealodGame();
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	static Board gameBoard;
	static void CreateBall();
	static void PutBall();
	static vector <Ball>  _ballsMap;
	static vector <Ball> _newBalls;
	static vector <BallColor> _AllColors;
	static FMOD::Sound* _sounds[MAX_SOUNDS];
	static void SelectSimplePath();	
	static unsigned int _StartCell;
	static unsigned int _EndCell;
	static FMOD::System* _system;		// Sound system
	static vector <int> _coords;

	static map<vector<int> ,Ball>	_BallMap;			// the main data base (STL)

	static vector <Ball> _Balls;



	static void BumBum();

	static bool _canAddBalls;
	GameController();

	static int _BallCounter;
	static void FloorDoAllSimple();

	

	static unsigned int _PostRedisplay;
};
