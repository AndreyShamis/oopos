#pragma once
#include "Graph.h"
#include "Vertex.h"
//#include "GraphIterator.h"

enum GAME_MODE
{
	_PLAY = 1,
	_MENU = 2,

};

class GameController
{
public:
	static GameController *getInst();
	static void mouseButton(int button, int state, int x, int y);
	static void selectFromMenu(int commandId);
	static void resizeWindow(int w, int h);
	static void GameController::LoadCallBacksForGlut();
	static void LoadGame();
	static void idle();
	static void display();

private:

	static Graph<Vertex>  _someGraph;
	// Window size in pixels
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	GameController();
	GAME_MODE	_GameMod;
};
