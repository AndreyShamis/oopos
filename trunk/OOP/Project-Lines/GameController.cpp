#include "GameController.h"
#include <math.h>
//=============================================================================
// singletone
GameController *GameController::_instance = NULL;

// initialite static virables
int			GameController::_WindowHeight = 540;
int			GameController::_WindowWidth  = 540;

Graph<Floor>		GameController::_floors;

//=============================================================================

void GameController::KeyPress(unsigned char key, int x, int y)
{
	if(key == 'q')
	{
		exit(EXIT_SUCCESS);
	}
	else if(key == 'n')
	{
		;
	}

}

//=============================================================================
//	Function is used in loading class
void GameController::LoadGame()
{
	float startX = 0.02;
	float startY = 0.02;

	float asataX = 36.0*(1.0/_WindowWidth);
	float asataY = 36.0*(1.0/_WindowHeight);
	for (int i=0;i<9;i++)
	{
		for (int j=0;j<9;j++)
		{
			Floor newFloor(startX,startY);
			_floors.addVertex(newFloor);
			startY +=asataY;
		}
		startY = 0.02;
		startX +=asataX;
	}
}


//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
	{
	float xPos = ((float)x)/((float)(_WindowWidth-1));
	float yPos = ((float)y)/((float)(_WindowHeight-1));
	yPos = 1.0f-yPos;

	if(state == 1)
	{
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		for(;it != it.end() ;it++)
		{
			float _X = (*it)->getX();
			float _Y = (*it)->getY();
			if(_X <= xPos && (_X+0.36) >= xPos
				&&  _Y <= yPos && _Y+0.36 >= yPos)
			{
				(*it)->setFloorType(Selected);
				cout << "Founded\n";
				break;
			}
		}	

	}

	cout << "X:" << xPos << " --Y:" << yPos << "\n";
}

//=============================================================================
//	Dispaly function
void GameController::display()
{

	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	Graph<Floor>::GraphIterator<Floor> it(_floors);
	for(;it != it.end() ;it++)
	{
		(*it)->Draw();
	}	
	glFlush() ;									//	Glut
	//glutPostRedisplay();
	glutSwapBuffers();							//	Glut
	
}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	// we call the display function
	display();	

	static int lol;

	if(lol != 10)
	{
		LoadGame();
		lol = 10;
	}
}

//=============================================================================
GameController::GameController()
{
	//	Glut load call set i.e.
	char *argv[] = {"Lines"};
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (_WindowWidth,_WindowHeight); 
	glutInitWindowPosition (10,10);
	//glPointSize(15);
	glutCreateWindow ("Lines - By: Andrey Shamis AND Ilia Gaysinsky");
	glClearColor(1.0, 1.0, 1.0,0.0);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);		//	Glut
	glLoadIdentity();					//	Glut
	gluOrtho2D(0, _WindowWidth, 0, _WindowHeight);			//	Glut 
	//glOrtho(0, _WindowWidth, 0, _WindowHeight, -1.0,1.0);
	glutReshapeFunc(resizeWindow);	
	LoadCallBacksForGlut();			// load call back for graph	
	glutMainLoop();
}

//=============================================================================
// the function which load call back for glut 
void GameController::LoadCallBacksForGlut()
{
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);
	glutKeyboardFunc(KeyPress);
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
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}