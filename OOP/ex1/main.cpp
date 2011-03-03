#include "macros.h"
#include "Paint.h"

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
	glutCreateWindow ("Paint - Andrey Shamis & Ilia Gaysinski");
	glPointSize(3);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);

	int menu = glutCreateMenu (selectFromMenu);
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}