//
//
//  Generated by Andrey Shamis Ilia Gaysinski
//
//  @ Project : Paint
//  @ File Name : Paint.h
//  @ Date : 3/3/2011
//  @ Author : 
//
//


#if !defined(_PAINT_H)
#define _PAINT_H
#include "macros.h"
#include <iostream>
#include "Shape.h"
#include "Horizontal.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"
#include "Wheel.h"
#include "Vertical.h"
#include <vector>

using namespace std;

struct UndoRedoShape
{
	Shape * _old;
	Shape * _real;
};


class Paint 
{
public:
	vector <Shape *> _obj;
	//vector <_obj *> _objs;
	vector <Shape *> _undo_redo_obj;
	int menu_status;
	Paint();
	void ShowMenu();
	void DrowByStatus();
	void display();
	void mouseButton(const int &button, const int &state, const float &x, const float &y);
	void idle();
	void selectFromMenu(const int &id);
private:
	vector <UndoRedoShape>  _undo_redo;
};

#endif  //_PAINT_H
