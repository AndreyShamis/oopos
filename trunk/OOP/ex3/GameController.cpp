#include "GameController.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::LoadGame()
{

	Graph<Vertex>  someGraph;
	for(int i= 0; i< 5;i++)
	{
		float x = 0.1;
		float y = 0.2;
	   Vertex newVertex(x,y);
	   int id =someGraph.addVertex(newVertex);
	   
	   newVertex.SetID(id);

	}

}