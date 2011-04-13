#pragma once
#include "macros.h"
#include <time.h>
#include <iomanip>


#define TIMER_SIZE 40
using namespace std;

#define _NEW_GAME_CH	'n'
#define _LEVEL_CH		'l'
#define _HEX_CH			'h'
#define _QUAD_CH		'q'
#define _EXIT_CH		'x'
#define _SOLUTION_CH	's'

#define _NEW_GAME	1
#define _LEVEL		2
#define _HEXG		3
#define _QUAD		4
#define _EXIT		5
#define _SOLUTION	6

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
	static void CreateMenuForGlut();
private:
	static void Menu(int val);
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
	static time_t seconds;
	static short int _neighborSize;
	GameController();
	GAME_MODE	_GameMod;
	static void ElectricityQuadr(const int srcID,const int plc);
	static void ElectricityHexdr(const int srcID,const int plc);
	static int _ID_OF_CENTER_VERTEX;
	static int _pointSize;
	static char timer[TIMER_SIZE];
	static bool _update_timer;
};
