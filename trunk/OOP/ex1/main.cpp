#include "macros.h"
#include "Paint.h"

//ohad

Paint paint;
// Window size in pixels
int WindowHeight;
int WindowWidth;

void display() {
	paint.display();
}

void idle(){
	paint.idle();
}

void selectFromMenu(int commandId){
	paint.selectFromMenu(commandId);
}

void mnuSetShapeColor(int colorid){
	paint.mnuSetColor(colorid);
}
void mnuClear(int colorid){
	paint.clearFromMenu(colorid);
}

void mnuResize(int commandID){
	paint.mnuResize(commandID);
}
void mouseButton(int button, int state, int x, int y){
	float xPos = ((float)x)/((float)(WindowWidth-1));
	float yPos = ((float)y)/((float)(WindowHeight-1));
	yPos = 1.0f-yPos;
	paint.mouseButton(button,state,xPos,yPos);
}

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

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500,500); 
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Paint");
	glPointSize(3);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);
	int shapesMenu = glutCreateMenu (selectFromMenu);
	glutAddMenuEntry ("Point\tp",		_DOT);
	glutAddMenuEntry ("Rect\tr",		_RECTANGLE);
	glutAddMenuEntry ("Square\ts",		_SQUARE);
	glutAddMenuEntry ("Circle\tc",		_CIRCLE);
	glutAddMenuEntry ("Wheel\tw",		_WHEEL);
	glutAddMenuEntry ("Circle Hole\tw", _CIRCLE_HOLE);
	glutAddMenuEntry ("Horisontale\tc", _H_LINE);
	glutAddMenuEntry ("Verticale\tw",	_V_LINE);
	glutAddMenuEntry ("Triangle\tw",	_TRIANGLE);

	int colorMenu = glutCreateMenu (mnuSetShapeColor);
	glutAddMenuEntry ("Red\tp",			_RED);
	glutAddMenuEntry ("White\tr",		_WHITE);
	glutAddMenuEntry ("Blue\ts",		_BLUE);
	glutAddMenuEntry ("Green\tc",		_GREEN);
	glutAddMenuEntry ("Black\tc",		_BLACK);


	int resizeMenu = glutCreateMenu (mnuResize);
	glutAddMenuEntry ("Grow selected\tp",		_GROW_SELETED);
	glutAddMenuEntry ("Shrink selected\tr",		_SHRINK_SELETED);
	glutAddMenuEntry ("Same size\ts",			_SAME_SIZE);

	int clearMenu	=	glutCreateMenu(mnuClear);
	glutAddMenuEntry ("Selected\tp",		_CLR_SELECTED);
	glutAddMenuEntry ("Same type\tr",		_CLR_SAME_TYPE);
	glutAddMenuEntry ("Same color\ts",		_CLR_SAME_COLOR);
	glutAddMenuEntry ("All",				_CLEAR_SCREEN);

	int menu = glutCreateMenu (selectFromMenu);
	glutAddSubMenu ("Shape",		shapesMenu);
	glutAddMenuEntry ("",		NULL);
	glutAddSubMenu ("Set Color",	colorMenu);
	glutAddMenuEntry ("",		NULL);
	glutAddMenuEntry ("Remove Mark",		_REMOVE_MARK);

	glutAddSubMenu ("Resize",		resizeMenu);
	glutAddSubMenu ("Clear",	clearMenu);
	glutAddMenuEntry ("Next Shape",		_NEXT_SHAPE);
	glutAddMenuEntry ("Prev Shape",		_PREV_SHAPE);
	glutAddMenuEntry ("Exit\tEsc",		_EXIT_PROGRAM);
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}