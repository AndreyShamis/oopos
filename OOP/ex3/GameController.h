#pragma once
#include "macros.h"
#include <time.h>
#include <iomanip>


#define TIMER_SIZE 10
using namespace std;
//============================ Enum section ===================================
enum graphKind {Quad, Hexagonal}; // define graph type

enum GAME_MODE						// define game mods
{
	_PLAY ,
	_MENU,

};

//============================ Structur section ===============================
struct AddEdges
{
	int vert1;
	int vert2;
};


class GameController
{
public:
	static void glutPrint(float x, float y, char* text, float r, float g, float b, float a);
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
	static void GraphGrinder();
	static time_t time_game;
	static short int _neighborSize;
	GameController();
	GAME_MODE	_GameMod;
	static void ElectricityQuadr(const int srcID,const int plc);
	static void ElectricityHexdr(const int srcID,const int plc);
	static int _ID_OF_CENTER_VERTEX;
	static int _pointSize;
	static char timer[TIMER_SIZE];
};
