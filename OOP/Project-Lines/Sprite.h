/*
	Sprite class
*/

#pragma once
#include "macros.h"
#include "Config.h"
#include <fstream>
#include <iostream>
//#include <glut.h>
#include <string.h>
#include <vector>



using namespace std;
class Sprite
{

public:
	//=============================================================================
	// Constructor
	Sprite(char* filename);
	Sprite(void);

	//=============================================================================
	//	Draw function
	//void Draw(const float &cordX, float &cordY);
	void Sprite::Draw(const float &cordX, float &cordY);
	void Sprite::DrowSprite(const float &cordX, float &cordY, short int alpha);
	//=============================================================================
	//	return height
	int getHeight();
	//=============================================================================
	//	return width
	int getWidth();
	void setSelected();
	void unSelect();
	void StartTurnOff();
	void StartTurnOn();

private:
	 //GraficLoader _temp;
	//static 
	//static	
	bool _selected;
		RGBA **_image;
	//static 
		int _height;		//	height of image
	//static 
		int _width;			//	width of image
		short int _alpha;
		bool _turnOff;
		bool _born;

	
};
