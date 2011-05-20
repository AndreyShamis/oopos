#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <GL/glut.h>
#include <glut.h>				//	USED IN OUR VERSION OF GLUT

#include <stdio.h>
#pragma once
using namespace std;



class GameController
{
public:
	static GameController *getInst();
	static void mouseButton(int button, int state, int x, int y);
	static void selectFromMenu(int commandId);
	static void resizeWindow(int w, int h);
	static void GameController::LoadCallBacksForGlut();
	static void LoadGame();
	static void idle();
	static void display();
	static void KeyPress(unsigned char key, int x, int y);
private:
	static int _WindowHeight;
	static int _WindowWidth;
	static GameController *_instance;
	GameController();
};
