#include "GameController.h"
//#include "Sprite.h"
#include <math.h>
//=============================================================================
// singletone
GameController *GameController::_instance = NULL;

// initialite static virables
int			GameController::_WindowHeight = WINDOW_HEIGHT;
int			GameController::_WindowWidth  = WINDOW_WIDTH;
bool		GameController::ones = true;

Board		GameController::gameBoard(-1.0f,0.f);


Graph<Ball>			GameController::_balls;
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
	srand((int)NULL);
	

	float startX = 0.2025;
	float startY = 0.063;

	unsigned int prev_vertex = 0;
	float offsetX = FLOOR_SIZE/_WindowWidth;
	float offsetY = FLOOR_SIZE/_WindowHeight;


	for (int i=0;i<9;i++)
	{
		prev_vertex = 0;
		for (int j=0;j<9;j++)
		{
			Floor newFloor(startX,startY);
			unsigned int newVert = _floors.addVertex(newFloor);
			
			if(prev_vertex)
			{
				   _floors.addEdge(prev_vertex,newVert);
				   prev_vertex = newVert;

			}
			if(i == rand()%6 || i/3 == j )
			{
				//;
				Ball newBall(startX,startY,Yellow);
				_balls.addVertex(newBall);
			}
			else if(i/2 == rand()%(j+1)) 
			{
				//;
				Ball newBall(startX,startY,Blue);
				_balls.addVertex(newBall);
			}
			else if(rand()%5 == 2)
			{
				Ball newBall(startX,startY,Green);
				_balls.addVertex(newBall);
			}
			else if(rand()%5 == 3)
			{
				Ball newBall(startX,startY,Red);
				_balls.addVertex(newBall);
			}

			startY +=offsetY;
		}
		startY =0.063;
		startX +=offsetX;
	}
}


//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
	{
	float xPos = ((float)x)/((float)(WINDOW_WIDTH));
	float yPos = ((float)y)/((float)(WINDOW_HEIGHT));
	yPos = 1.0f-yPos;

	if(state == 1)
	{
		static float CELL_SIZE_X = FLOOR_SIZE/_WindowWidth;
		static float CELL_SIZE_Y = FLOOR_SIZE/_WindowHeight;
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		for(;it != it.end() ;it++)
		{
			float _X = (*it)->getX();
			float _Y = (*it)->getY();
			if(_X <= xPos-CELL_SIZE_X  && (_X+CELL_SIZE_X ) > xPos-CELL_SIZE_X 
				&&  _Y <= yPos && _Y+CELL_SIZE_Y> yPos)
			{
				(*it)->setFloorType(Selected);
				//cout << "Founded\n";
				cout << "objX:" << _X << " objY:" << _Y <<  "\n";
				cout << "objX'" << _X+CELL_SIZE_X  << " objY':" << _Y+CELL_SIZE_Y << "\n";
				break;
			}
		}	
		cout << "X:" << xPos << " --Y:" << yPos << "\n";
	}

	
}

//=============================================================================
//	Dispaly function
void GameController::display()
{

	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	gameBoard.Draw();

	Graph<Floor>::GraphIterator<Floor> it(_floors);
	for(;it != it.end() ;it++)
	{
		(*it)->Draw();
	}
	Graph<Ball>::GraphIterator<Ball> itb(_balls);
	for(;itb != itb.end() ;itb++)
	{
		(*itb)->Draw();
	}	
	glFlush() ;									//	Glut
	//
	glutSwapBuffers();							//	Glut
	
}

//=============================================================================
//	Dispaly function
void GameController::display2()
{

	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	gameBoard.Draw();		// ZAKOMENTIRUI SHTOB NE GRUZILA

	glFlush() ;									//	Glut
	//
	glutSwapBuffers();							//	Glut
	
}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	// we call the display function
	//display();	

	static int lol;

	if(lol < 10)
	{
		LoadGame();
		lol = 10;
	}

	lol++;

	if(lol == 1000)
	{
		glutPostRedisplay();
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
	//glPointSize(POINT_SIZE/WINDOW_HEIGHT);
	glutCreateWindow ("Lines - By: Andrey Shamis AND Ilia Gaysinsky");
	glClearColor(1.0, 1.0, 1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);							//	Glut//
	glLoadIdentity();										//	Glut
	//gluOrtho2D(0, _WindowWidth, 0, _WindowHeight);			//	Glut 
	//glOrtho(0, _WindowWidth, 0, _WindowHeight, -1.0,1.0);
	glutReshapeFunc(resizeWindow);	
	LoadCallBacksForGlut();			// load call back for graph	
	glutMainLoop();
}

//=============================================================================
// the function which load call back for glut 
void GameController::LoadCallBacksForGlut()
{
	if(ones)
	{	
		glutDisplayFunc(display2);// ZAKOMENTIRUI SHTOB NE GRUZILA  
		ones = false;
	}
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
	_WindowWidth =  (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	//gluOrtho2D(0, _WindowWidth, 0, _WindowHeight);			//	Glut 
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