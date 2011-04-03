#include "GameController.h"

GameController::GameController()
{
	glMatrixMode(GL_PROJECTION);		//	Glut
    glLoadIdentity();					//	Glut
    gluOrtho2D(0, 500, 0, 500);			//	Glut
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