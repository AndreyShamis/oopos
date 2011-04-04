#pragma once
#include "Graph.h"
#include "Vertex.h"
#include "GraphIterator.h"

class GameController
{
public:
	static GameController *getInst();

	void LoadGame();
	void idle()
	{
		 Display();
	}
	void Display()
	{
		;
	}
private:
	static GameController *_instance;
	GameController();
};
