#include "GameController.h"

GameController *GameController::_instance = NULL;

//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}

GameController::GameController()
{

	glMatrixMode(GL_PROJECTION);		//	Glut
    glLoadIdentity();					//	Glut
    gluOrtho2D(0, 500, 0, 500);			//	Glut 
}

void GameController::LoadGame()
{

	Graph<Vertex>  someGraph;

	cout << "Hi\n";

	for(int i= 0; i< 5;i++)
	{
		float x = 0.1;
		float y = 0.2;
	   Vertex newVertex(x,y);
	   int id =someGraph.addVertex(newVertex);
	   
	   newVertex.SetID(id);

	}

	//Graph<Vertex>::GraphIterator<Vertex> it(&someGraph);
	GraphIterator<Vertex> it(&someGraph);

	for(;it.end();it++)
	{
		cout << "Ya ";// <<;
		cout << it.getCurent()->GetID() << "\n";

	}



}