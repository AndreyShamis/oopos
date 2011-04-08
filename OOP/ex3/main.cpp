
#include "macros.h"
#include "GameController.h"

////=============================================================================
//// the function which provide mouse button
//void mouseButton(int button, int state, int x, int y){
//	float xPos = ((float)x)/((float)(WindowWidth-1));
//	float yPos = ((float)y)/((float)(WindowHeight-1));
//	yPos = 1.0f-yPos;
//	//Paint::getInst()->mouseButton(button,state,xPos,yPos);
//}
//=============================================================================
// the function which provide key press
//void KeyPress(unsigned char key, int x, int y)
//{
//	float xPos = ((float)x)/((float)(WindowWidth-1));
//	float yPos = ((float)y)/((float)(WindowHeight-1));
//	yPos = 1.0f-yPos;
//	//Paint::getInst()->KeyPress(key,xPos,yPos);
//}
////=============================================================================
//// the function which provide resize window
//void resizeWindow(int w, int h){
//	WindowHeight = (h>1) ? h : 2;
//	WindowWidth = (w>1) ? w : 2;
//	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}

////=============================================================================
//// the function which load call back for glut 
//void LoadCallBacksForGlut()
//{
//	glutIdleFunc(idle);
//	glutDisplayFunc(display);  
//	//glutMouseFunc (mouseButton);
//	glutKeyboardFunc(KeyPress);
//}
//=============================================================================
// main function
int main(int argc, char** argv){


	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (600,600); 
	glutInitWindowPosition (100,100);
	//glPointSize(15);
	glutCreateWindow ("Lights - Andrey Shamis AND Ilia Gaysinsky");
	glClearColor(0.0, 0.0, 0.0,0.0);

	GameController::getInst()->LoadGame();
	glutMainLoop();
	return 0;
}
//=============================================================================
//=============================================================================
//=============================================================================