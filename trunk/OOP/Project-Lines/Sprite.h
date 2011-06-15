/*
	Sprite class
*/

#pragma once
#include "macros.h"
#include "Config.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
class Sprite
{

public:
	//=============================================================================
	// Constructor
	Sprite(char* filename);
	//=============================================================================
	//	Draw function
	void Sprite::Draw(const float &cordX, float &cordY);
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

	bool _selected;
	RGBA **_image;
	int _height;		//	height of image
	int _width;			//	width of image
	short int _alpha;
	bool _turnOff;
	bool _born;

	
};
