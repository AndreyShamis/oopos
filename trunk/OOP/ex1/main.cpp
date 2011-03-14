#include "macros.h"
#include "Paint.h"

//ohad

//Paint paint;
// Window size in pixels
int WindowHeight;
int WindowWidth;

//=============================================================================
//
void display() {
	Paint::getInst()->display();
}
//=============================================================================
// the function which called to idel
void idle(){
	Paint::getInst()->idle();
}

//=============================================================================
// the function which provide  select from menu
void selectFromMenu(int commandId){
	Paint::getInst()->selectFromMenu(commandId);
}

//=============================================================================
// the function which provide menu set shape color
void mnuSetShapeColor(int colorid){
	Paint::getInst()->mnuSetColor(colorid);
}
//=============================================================================
// the function which provide menu clear
void mnuClear(int colorid){
	Paint::getInst()->clearFromMenu(colorid);
}

//=============================================================================
// the function which provide  menu resize
void mnuResize(int commandID){
	Paint::getInst()->mnuResize(commandID);
}
//=============================================================================
// the function which provide mouse button
void mouseButton(int button, int state, int x, int y){
	float xPos = ((float)x)/((float)(WindowWidth-1));
	float yPos = ((float)y)/((float)(WindowHeight-1));
	yPos = 1.0f-yPos;
	Paint::getInst()->mouseButton(button,state,xPos,yPos);
}
//=============================================================================
// the function which provide key press
void KeyPress(unsigned char key, int x, int y)
{
	float xPos = ((float)x)/((float)(WindowWidth-1));
	float yPos = ((float)y)/((float)(WindowHeight-1));
	yPos = 1.0f-yPos;
	Paint::getInst()->KeyPress(key,xPos,yPos);
}
//=============================================================================
// the function which provide resize window
void resizeWindow(int w, int h){
	WindowHeight = (h>1) ? h : 2;
	WindowWidth = (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//=============================================================================
// the function which create menu for glut
void CreateMenuForGlut()
{
	int shapesMenu = glutCreateMenu (selectFromMenu);
	glutAddMenuEntry ("Point\t",			_DOT);
	glutAddMenuEntry ("Rectangle\t",		_RECTANGLE);
	glutAddMenuEntry ("Empty Rectangle\t",	_EMPTY_RECTANGLE);
	glutAddMenuEntry ("Square\t",			_SQUARE);
	glutAddMenuEntry ("Circle\t",			_CIRCLE);
	glutAddMenuEntry ("Wheel\t",			_WHEEL);
	glutAddMenuEntry ("Empty Circle\t",		_EMPTY_CIRCLE);
	glutAddMenuEntry ("Horisontale\t",		_H_LINE);
	glutAddMenuEntry ("Verticale\t",		_V_LINE);
	glutAddMenuEntry ("Itriangle\t",		_ITRIANGLE);
	glutAddMenuEntry ("Equiangular\t",		_EQUIANGULAR);

	int colorMenu = glutCreateMenu (mnuSetShapeColor);
	glutAddMenuEntry ("Red\t",			_RED);
	glutAddMenuEntry ("White\t",		_WHITE);
	glutAddMenuEntry ("Blue\t",			_BLUE);
	glutAddMenuEntry ("Green\t",		_GREEN);
	glutAddMenuEntry ("Black\t",		_BLACK);

	int resizeMenu = glutCreateMenu (mnuResize);
	glutAddMenuEntry ("Grow selected\t+",		_GROW_SELETED);
	glutAddMenuEntry ("Shrink selected\t-",		_SHRINK_SELETED);
	glutAddMenuEntry ("Same size\tCtrl+_",		_SAME_SIZE);

	int clearMenu	=	glutCreateMenu(mnuClear);
	glutAddMenuEntry ("Selected\tDelete",		_CLR_SELECTED);
	glutAddMenuEntry ("Same type\tShift+d",		_CLR_SAME_TYPE);
	glutAddMenuEntry ("Same color\tShift+c",	_CLR_SAME_COLOR);
	glutAddMenuEntry ("All\tShift+a",			_CLEAR_SCREEN);

	int menu = glutCreateMenu (selectFromMenu);
	glutAddSubMenu ("Shape",						shapesMenu);
	glutAddSubMenu ("Set Color",					colorMenu);
	glutAddMenuEntry ("Remove Mark\tSpace",			_REMOVE_MARK);
	glutAddSubMenu ("Resize",		resizeMenu);
	glutAddSubMenu ("Clear",		clearMenu);
	glutAddMenuEntry ("Next Shape\tShift+z",		_NEXT_SHAPE);
	glutAddMenuEntry ("Prev Shape\tShift+x",		_PREV_SHAPE);
	glutAddMenuEntry ("Undo\tCtrl+z",				_UNDO);
	glutAddMenuEntry ("Exit\tEsc",					_EXIT_PROGRAM);
	glutAttachMenu (GLUT_RIGHT_BUTTON);

}
//=============================================================================
// the function which load call back for glut 
void LoadCallBacksForGlut()
{
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);
	glutKeyboardFunc(KeyPress);
}
//=============================================================================
// main function
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500,500); 
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Paint");
	glPointSize(3);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutReshapeFunc(resizeWindow);
	LoadCallBacksForGlut();
	CreateMenuForGlut();
	glutMainLoop();
	return 0;
}
//=============================================================================
//=============================================================================
//=============================================================================