#include "GameController.h"
#include <math.h>
//=============================================================================
// single tone
GameController *GameController::_instance = NULL;

// initialite static virables
int			GameController::_WindowHeight;
int			GameController::_WindowWidth;

Graph<Floor>		GameController::_floors;


//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}

void GameController::KeyPress(unsigned char key, int x, int y)
{

	if(key == 'q')
	{


		exit(EXIT_SUCCESS);
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
	glutInitWindowSize (940,540); 
	glutInitWindowPosition (10,10);
	//glPointSize(15);
	glutCreateWindow ("Lines - By: Andrey Shamis AND Ilia Gaysinsky");
	glClearColor(1.0, 1.0, 1.0,0.0);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);		//	Glut
	glLoadIdentity();					//	Glut
	gluOrtho2D(0, 940, 0, 540);			//	Glut 
	glOrtho(0, 940, 0, 540, -1.0,1.0);
	glutReshapeFunc(resizeWindow);	
	LoadCallBacksForGlut();			// load call back for graph	
	glutMainLoop();


	
}
//=============================================================================
//	Function is used in loading class
void GameController::LoadGame()
{
	float startX = 0.02;
	float startY = 0.02;

	float asataX = 36.0*(1.0/940);
	float asataY = 36.0*(1.0/540);
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

	//cout << "X:" << x << " --Y:" << y << "\n";
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
	glutKeyboardFunc(KeyPress);
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

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	//float rads = (3.1415926535/180);
	//float _x = 0.2;
	//float _y = 0.3;
	//const float hfSz =	 0.2/2;				//	get Helf size between
	////	two neigbors
	//const float proportion = 360/4;	//	angle between neighobrs
	//const int vecSize = 4;	//	Get vector size
	//for(int i=0;i<vecSize;i++)
	//{
	//	if(1 == 1)
	//	{
	//		glBegin(GL_LINES);							// Start drawing a vertical
	//		glColor3f(0.4, 0.8, 0.0);  	// Set color of shape
	//		// set points of shape
	//		glVertex2f (_x, _y);								
	//		glVertex2f (_x - hfSz*cos(float(i*proportion)*rads), _y - hfSz*sin(float(i*proportion)*rads));	
	//		glEnd();									// End of drawing a vertical
	//	}
	//}

	//// Start drawing a dot 
	//glEnable(GL_POINT_SMOOTH);
	//glBegin(GL_POINTS);
	//// set point size

	//glColor3f(0.3, 0.4, 0.0);	// Set color of shape
	//glVertex2f (_x, _y);						// set point of shape		

	//glEnd();		


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
