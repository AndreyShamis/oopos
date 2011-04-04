#include "GameController.h"
//=============================================================================
GameController *GameController::_instance = NULL;

//=============================================================================


int	GameController::_WindowHeight;
int	GameController::_WindowWidth;
Graph<Vertex>  GameController::_someGraph;
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

	_GameMod = _MENU;
}

void GameController::LoadGame()
{
	glutReshapeFunc(resizeWindow);
	LoadCallBacksForGlut();








	

	cout << "Hi\n";
	
	int row_size = 9;
	int col_size = row_size;
	int prev_id=0;
	for(int i= 0; i< row_size;i++)
	{
		prev_id=0;
		for(int j= 0; j< col_size;j++)
		{
			float x = (float)(i+0.1)/row_size;
			float y = (float)(j+0.1)/col_size;
			Vertex newVertex(x,y);
			int id =_someGraph.addVertex(newVertex);
	   
			newVertex.SetID(id);
			if(prev_id)
				_someGraph.addEdge(prev_id,id);

			if(i)
				_someGraph.addEdge(id-row_size,id);

			prev_id=id;
			
		}

	}													   



	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
//		GraphIterator<Vertex> it(&someGraph);
	//GraphIterator<Vertex> it(&someGraph);

	for(;it != _someGraph.end() ;it++)
	{
		cout << "Ya ";// <<;
		cout << (*it)->GetID() << "\n";

	}



}

//void gameController::idle()
//{
//
//	//glutPostRedisplay();				//	glut call
//	
//}

//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
{
	float xPos = ((float)x)/((float)(_WindowWidth-1));
	float yPos = ((float)y)/((float)(_WindowHeight-1));
	yPos = 1.0f-yPos;
	//Paint::getInst()->mouseButton(button,state,xPos,yPos);
}

//=============================================================================
// the function which provide  select from menu
void GameController::selectFromMenu(int commandId)
{
	//Paint::getInst()->selectFromMenu(commandId);
}

//=============================================================================
// the function which provide resize window
void GameController::resizeWindow(int w, int h)
{
	_WindowHeight = (h>1) ? h : 2;
	_WindowWidth = (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//=============================================================================
// the function which load call back for glut 
void GameController::LoadCallBacksForGlut()
{
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);
	//glutKeyboardFunc(KeyPress);

	//	Sound Play
	//sndPlaySound(L"SOUND/BackGround_Sound.wav", SND_LOOP | SND_ASYNC );
}

//=============================================================================
//	Dispaly function
void GameController::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);

	for(;it != _someGraph.end() ;it++)
	{
		(*it)->Draw();
	}

	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut

}

//=============================================================================
//	Idle function 
void GameController::idle()
{

	//if(_GameMod == _PLAY)
		display();			//	call display function

	//if(_GameMod == _MANU)
	//	;
}
