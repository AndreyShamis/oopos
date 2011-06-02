#include "Graph.h"
#include "Sprite.h"
#include "Floor.h"
#include "Cell.h"
#include "Ball.h"
#include "Board.h"
#include "macros.h"
#include <map>
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

	static void RealodGame();
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	static Board gameBoard;
	static void CreateBall();
	static void PutBall();
	static vector <Ball> _newBalls;
	static void SelectSimplePath();	
	static unsigned int _StartCell;
	static unsigned int _EndCell;

	static vector <Ball>  _ballsMap;
	static void BumBum();

	static bool _canAddBalls;
	GameController();

	static int _BallCounter;
	static void FloorDoAllSimple();

	static vector <BallColor> _AllColors;

	static unsigned int _PostRedisplay;
};
