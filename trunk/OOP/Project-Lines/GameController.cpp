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


bool		GameController::_canAddBalls;
unsigned int GameController::_StartCell;
unsigned int GameController::_EndCell;

vector <Ball>	GameController::_newBalls;
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

void GameController::SelectSimplePath()
{

	

}

void GameController::CreateBall()
{
	int newBallColor=0;
	vector <BallColor> _AllColors;

	_AllColors.push_back(Green);
	_AllColors.push_back(White);
	_AllColors.push_back(Black);
	_AllColors.push_back(Yellow);
	_AllColors.push_back(Orange);
	_AllColors.push_back(Blue);
	_AllColors.push_back(Red);
	_AllColors.push_back(Mixed);
	_AllColors.push_back(OrangeRed);
	_AllColors.push_back(WhiteBlue);
	_AllColors.push_back(greenYellow);

	int i = 0;

	int newBallsSize = rand()%4+1;
	float startX = 0.8225;
	float startY = 0.183;
	while (i <=newBallsSize)
	{
		newBallColor = rand()%11;
		Ball newBall(startX,startY,_AllColors[newBallColor]);
		_newBalls.push_back(newBall);
		i++;
		startY+=0.08;
	}

}
void GameController::PutBall()
{

	float startX = 0.2025;
	float startY = 0.063;
	float offsetX = FLOOR_SIZE/_WindowWidth;
	float offsetY = FLOOR_SIZE/_WindowHeight;

	while(_newBalls.size())
	{
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		for(;it != it.end() &&  _newBalls.size();it++)
		{
			if(!(*it)->getBalled() && rand()%20 == 1)
			{
				
				_newBalls[0].setX((*it)->getX());
				_newBalls[0].setY((*it)->getY());
				_newBalls[0].setID((*it)->getID());	//	set ball id like cell id
				_balls.addVertex(_newBalls[0]);
				_newBalls.erase(_newBalls.begin()) ;

				(*it)->setBalled(true);
				_floors.tempDetach((*it)->getID(),true);

			}
		}

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

	vector <unsigned int> _prevLine;
	vector <unsigned int> _thisLine;
	int edge_c = 0;
	for (int i=0;i<9;i++)
	{
		prev_vertex = 0;
		for (int j=0;j<9;j++)
		{
			Floor newFloor(startX,startY);
			unsigned int newVert = _floors.addVertex(newFloor);
			_floors.getData(newVert)->setID(newVert);

			_thisLine.push_back(newVert);
			if(i>0)
			{
				cout << "Add edge|:" << edge_c<< ":"<<_floors.addEdge(_prevLine[j],_thisLine[j]) << "\n";
				edge_c++;
			}
			if(prev_vertex)
			{
				cout << "Add edge-:" << edge_c<< ":" << _floors.addEdge(prev_vertex,newVert) << "\n";
				
				edge_c++;
			}		 
			prev_vertex = newVert;
			/*
			if(i == rand()%6)
			{
				Ball newBall(startX,startY,Yellow);
				_balls.addVertex(newBall);
			}
			else if(rand()%15 == 2)
			{
				Ball newBall(startX,startY,Green);
				_balls.addVertex(newBall);
			}
			else if(rand()%7 == 3)
			{
				Ball newBall(startX,startY,Red);
				_balls.addVertex(newBall);
			}	   */

			startY +=offsetY;
		}
		startY =0.063;
		startX +=offsetX;
		_prevLine.clear();
		_prevLine = _thisLine;
		_thisLine.clear();
	}

	CreateBall();
	PutBall();
	CreateBall();
	
	cout << "Size : " << _floors.countEdges() << "\n";
}


void GameController::mouseMove(int x,int y)
{

	if(_StartCell>0)
	{
	
		float xPos = ((float)x)/((float)(WINDOW_WIDTH));
		float yPos = ((float)y)/((float)(WINDOW_HEIGHT));
		yPos = 1.0f-yPos;

		static float CELL_SIZE_X = FLOOR_SIZE/_WindowWidth;
		static float CELL_SIZE_Y = FLOOR_SIZE/_WindowHeight;
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		int _prevEndCell = _EndCell;
		//_EndCell = 0;
		
		
		for(;it != it.end() ;it++)
		{
			float _X = (*it)->getX();
			float _Y = (*it)->getY();
			if(_X <= xPos-CELL_SIZE_X  && (_X+CELL_SIZE_X ) > xPos-CELL_SIZE_X 
				&&  _Y <= yPos && _Y+CELL_SIZE_Y> yPos)
			{
				//(*it)->setFloorType(Selected);

				if(!(*it)->getBalled())
				{
					_EndCell = (*it)->getID();
					_canAddBalls = true;
				}
				else
				{


					_canAddBalls = false;
				}
				break;
			}
		}
		Graph<Floor>::GraphIterator<Floor> itSimple(_floors);
		for(;itSimple != itSimple.end() ;itSimple++)
		{
			(*itSimple)->setFloorType(Simple);
		}
		if( _EndCell && _StartCell != _EndCell)
		{
			//cout << "Enter to check\n";

			_floors.tempDetach(_StartCell,false);
			vector<int> _bfsVec = _floors.getVectorOfIdsBFS(_StartCell);
			
			//cout <<"Vec size : " << _bfsVec.size() << "\n";
			int _inVec=0;

			
			for (int i=0;i<(int)_bfsVec.size();i++)
			{
				if(_bfsVec[i] == _EndCell)
				{
					//cout << "Found last and him:" << _bfsVec[i] << "\n";
					_inVec = _bfsVec[i];
					break;
				}
			}
			for(;it != it.end() ;it++)
			{
				(*it)->setFloorType(Simple);
			}	
			//_inVec = _EndCell;
			while(true)
			{
				if(_inVec > 0)
				{
			//		cout << "Work with: " << _inVec << "\n";
					_floors.getData(_inVec)->setFloorType(Selected);
					_inVec = _floors.getBfsDfsFather(_inVec);
				}
				else
				{
					break;
				}
			}
			_floors.tempDetach(_StartCell,true);
		}
	}	//	End condition if _Start selected
}
//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
	{
	float xPos = ((float)x)/((float)(WINDOW_WIDTH));
	float yPos = ((float)y)/((float)(WINDOW_HEIGHT));
	yPos = 1.0f-yPos;

	if(state == 0)
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
				//(*it)->setFloorType(Selected);
				
				if((*it)->getBalled())
					_StartCell = (*it)->getID();
				else
				   _StartCell =0;
				cout << "Founded Start CELL : " << _StartCell  << "\n";
				break;
			}
		}	
		//cout << "X:" << xPos << " --Y:" << yPos << "\n";
	}
	else if(state == 1)
	{

		Graph<Floor>::GraphIterator<Floor> itSimple(_floors);
		for(;itSimple != itSimple.end() ;itSimple++)
		{
			(*itSimple)->setFloorType(Simple);
		}
		if(_canAddBalls && _StartCell != _EndCell && _EndCell >0 && _StartCell>0)
		{

			Graph<Ball>::GraphIterator<Ball> itb(_balls);
			for(;itb != itb.end() ;itb++)
			{
				if((*itb)->getID() == _StartCell)
				{
					
					(*itb)->setID(_EndCell);
					(*itb)->setX(_floors.getData(_EndCell)->getX());
					(*itb)->setY(_floors.getData(_EndCell)->getY());
					_floors.tempDetach(_StartCell,false);
					_floors.tempDetach(_EndCell,true);

					_floors.getData(_EndCell)->setBalled(true);
					_floors.getData(_StartCell)->setBalled(false);
					PutBall();
					CreateBall();
					break;
				}
			}	



		}
		_StartCell = 0;
		_EndCell = 0;


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

	for(int i =0;i<(int)_newBalls.size();i++)
	{
		_newBalls[i].Draw();
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

	static unsigned int lol;

	if(lol < 10)
	{
		LoadGame();
		lol = 10;
	}

	lol++;

	if(lol == 10000)
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
	glutMotionFunc(mouseMove); 
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