#include "Graph.h"
#include "Sprite.h"
#include "Floor.h"
#include "Cell.h"
#include "Ball.h"
#include "Board.h"
#include "macros.h"
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
	static void GameController::LoadCallBacksForGlut();
	static void LoadGame();
	static void idle();
	static void display();
	static void display2();
	static void KeyPress(unsigned char key, int x, int y);
private:
	static Graph<Floor>		_floors;
	static Graph<Ball>		_balls;
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	static Board gameBoard;
	static bool ones;
	static void CreateBall();
	static void PutBall();
	static vector <Ball> _newBalls;
	static void SelectSimplePath();	
	static unsigned int _StartCell;
	static unsigned int _EndCell;

	static bool _canAddBalls;
	GameController();


};
