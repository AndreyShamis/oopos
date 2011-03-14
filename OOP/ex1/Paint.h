//
//  @ Project : Paint
//  @ File Name : Paint.h
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//	@ Description : A main class (singeltone) that implimen paint of shapes and
//	@ ather fichers				
//
#pragma once

#include "macros.h"
#include <iostream>
#include "Shape.h"
#include "Horizontal.h"
#include "Rectanglle.h"
#include "EmptyRectangle.h"
#include <windows.h> // for PlaySound()
#include "Square.h"
#include "Circle.h"
#include "EmptyCircle.h"
#include "Dot.h"
#include "Wheel.h"
#include "Vertical.h"
#include "Itriangle.h"
#include "Equiangular.h"
#include <vector>

using namespace std;

#define _GROW_DEFAULT_SIZE 0.1
#define _SHRINK_DEFAULT_SIZE 0.1

struct UndoShape
{
	RgbColor	_color;
	float		_size;
	Shape *obj;
};


class Paint 
{
public:
	static Paint *getInst();
	static Paint *_instance;
	
	void display();
	void mouseButton(const int &button, const int &state, const float &x, const float &y);
	void idle();
	void selectFromMenu(const int &id);
	void mnuSetColor(const int &color_value);
	void mnuResize(const int &commandID);
	void clearFromMenu(const int &id)	;

	void KeyPress(unsigned char key, const float  &x, const float  &y);
private:
	Paint();
	int _draw_figure;
	void ClearDB();
	vector <UndoShape>  _undo_changes;
	vector <Shape *> _obj;
	vector <Shape *> _undo_obj;
	
	int _actual_shape;

	RgbColor _colors[6];
	int		_color_id;
	void Error_Sound();
	void SetNextShape();
	void SetPreviousShape();
	void LoadColorsToMemory();	
	void ShrinkSelectedShape();
	void GrowSelectedShape();
	void SameSizeByShape();
	void ClearSelectedShape();
	void ClearBySameType();
	void ClearBySameColor();
	bool CompareColor(const RgbColor &val1,const RgbColor &val2)const;
	void UnSelect();

	// UNDO
	//	///
	
	
	int				_UndoType;
	unsigned int	_UndoRemove;
	int				_undoSelected;

	//	0 = Nothing
	//	1 = Remove New Object
	//  2 = Change All Object which Founded in Undo Object
	//	3 = Selection
	void Undo();
	void CreateUndo(const int typeOfUndo);
	void UndoPrepareRemove(const int &id);
	void UndoPrepareSelection(const int &prev_sh, const int &new_sh);
	void UndoNewObject();
	void UndoSelection();
	void UndoChangesOnObjects();
	void UndoPrepareChanges(Shape *shape_to_save,const int &id);
	void UndoRemoved();
};
