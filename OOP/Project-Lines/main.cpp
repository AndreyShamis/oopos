#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <GL/glut.h>
#include <glut.h>				//	USED IN OUR VERSION OF GLUT

#include <stdio.h>
#include "GameController.h"

//=============================================================================
// main function
int main(int argc, char** argv){
	GameController::getInst()->LoadGame();

	return 0;
}
//=============================================================================
//=============================================================================
//=============================================================================