#include "GameController.h"
//=============================================================================
// single tone
GameController *GameController::_instance = NULL;

// initialite static virables
int			GameController::_WindowHeight;
int			GameController::_WindowWidth;

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


}
//=============================================================================
GameController::GameController()
{
	//	Glut load call set i.e.
	char *argv[] = {"Lines"};
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (940,540); 
	glutInitWindowPosition (200,10);
	//glPointSize(15);
	glutCreateWindow ("Lines - Andrey Shamis AND Ilia Gaysinsky");
	glClearColor(0.0, 0.0, 0.0,0.0);
	glMatrixMode(GL_PROJECTION);		//	Glut
	glLoadIdentity();					//	Glut
	gluOrtho2D(0, 940, 0, 540);			//	Glut 
	glutReshapeFunc(resizeWindow);	
	LoadCallBacksForGlut();			// load call back for graph	
	glutMainLoop();


}
//=============================================================================
//	Function is used in loading class
void GameController::LoadGame()
{
	;
}


//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
	{
	float xPos = ((float)x)/((float)(_WindowWidth-1));
	float yPos = ((float)y)/((float)(_WindowHeight-1));
	yPos = 1.0f-yPos;

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



	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut

}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	// we call the display function
	display();	


}
