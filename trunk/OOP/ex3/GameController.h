#pragma once
#include "Graph.h"
#include "Vertex.h"

class GameController
{
public:
	void LoadGame();
	void idle()
	{
		 Display();
	}
	void Display()
	{
		;
	}
	GameController(void);
	~GameController(void);
};
