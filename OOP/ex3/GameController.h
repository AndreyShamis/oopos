#pragma once
#include "macros.h"
#include "Vertex.h"
#include "Graph.h"
#include <time.h>
#include <iomanip>
//#include "GraphIterator.h"

using namespace std;

enum graphKind {Quad, Hexagonal};

enum GAME_MODE
{
	_PLAY ,
	_MENU,

};

struct AddEdges
{
	int vert1;
	int vert2;
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
	static void createGameGraph();
	static void createFullGraph();
	static void creatQuadGraph(const int rowSize);
	static void creatHexagonalGraph(const int size);
	static void KeyPress(unsigned char key, int x, int y);

private:

	static void ClearAll();
	static void FindElectrecisty();
	static int _level;
	static bool _show_sol;
	static graphKind	_grKind;
	static int			_grSize;
	static Graph<Vertex>  _someGraph;
	static Graph<Vertex>  _FullGraph;
	static Graph<Vertex>  _Solution;
	// Window size in pixels
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	GameController();
	GAME_MODE	_GameMod;

	static int _ID_OF_CENTER_VERTEX;
};
