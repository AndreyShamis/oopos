//
//  @ Project : Paint
//  @ File Name : Paint.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#include "Paint.h"
Paint *Paint::_instance = NULL;

//=============================================================================
//	Return pointer to created? class-object
Paint *Paint::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new Paint();

	return(_instance);						//	Return the object pointer

}
//=============================================================================
//	Constructor
Paint::Paint()
{
	LoadColorsToMemory();				//	Glut
	glMatrixMode(GL_PROJECTION);		//	Glut
    glLoadIdentity();					//	Glut
    gluOrtho2D(0, 500, 0, 500);			//	Glut
	_actual_shape = 0;					//	No shape selected
	_draw_figure = _DOT;				//	Default shape 
	_color_id =_BLUE;					//	Default color

}

//=============================================================================
//	Compare color between two colors
bool Paint::CompareColor(const RgbColor &val1,const RgbColor &val2)const
{
	if(val1.r == val2.r && val1.g == val2.g && val1.r == val2.r)
		return(true);					//	return true eq

	return false;						//	nor eq

}

//=============================================================================
//	Load colors to memory function
void Paint::LoadColorsToMemory()
{
	//	Load geen
	_colors[_GREEN].r = 0.0;
	_colors[_GREEN].g = 1.0;
	_colors[_GREEN].b = 0.0;

	//	Load black
	_colors[_BLACK].r = 0.0;
	_colors[_BLACK].g = 0.0;
	_colors[_BLACK].b = 0.0;

	//	Load white
	_colors[_WHITE].r = 1.0;
	_colors[_WHITE].g = 1.0;
	_colors[_WHITE].b = 1.0;

	//	Load red
	_colors[_RED].r = 1.0;
	_colors[_RED].g = 0.0;
	_colors[_RED].b = 0.0;

	//	Load blue
	_colors[_BLUE].r = 0.0;
	_colors[_BLUE].g = 0.0;
	_colors[_BLUE].b = 1.0;

	//	Load gray
	_colors[_GRAY].r = 0.7;
	_colors[_GRAY].g = 0.7;
	_colors[_GRAY].b = 0.7;
}

//=============================================================================
//	Play error Sound
void Paint::Error_Sound()
{
	sndPlaySound(L"Error.wav",NULL );
}

//=============================================================================
//	Dispaly function
void Paint::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	//	For all object in vector run draw
	for(int i=0;i<(int)_obj.size();i++)
	{
		//	Check if the object selected
		if( i == _actual_shape-1)				
		{	
			//	Change for time the color of object to gray color
			const RgbColor temp = _obj[i]->GetColor();
			_obj[i]->SetColor(_colors[_GRAY]);  //	Set new color
			_obj[i]->Draw();					//	Draw
			_obj[i]->SetColor(temp);			//	Set old color
		}
		else
			_obj[i]->Draw();					//	Draw
	}
	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut

}

//=============================================================================
//	Function to clear all object from the memory
void Paint::ClearDB()
{
	for(int i=0;i<(int)_obj.size();i++)
		_undo_obj.push_back(_obj[i]);	//	Push to UNDO

	_obj.clear();					//	delete all objects
}

//=============================================================================
//
void Paint::selectFromMenu(const int &id)
{
	_draw_figure = id;					//	set type of figure wich gonna be
										//	drawed
	switch(_draw_figure)
	{
	case _PREV_SHAPE:					//	Get preview shape
		SetPreviousShape();
		break;
	case _NEXT_SHAPE:					//	Get next shape
		SetNextShape();
		break;	
	case _REMOVE_MARK:					//	Remove mark
		UnSelect();
		break;	
	case _UNDO:							//	Undo
		Undo();
		break;	
	case _EXIT_PROGRAM:					//	Exir program
		exit(EXIT_SUCCESS);
		break;
	}

}

//=============================================================================
//	Clear selected shape if no shape selected do nothing
void Paint::ClearSelectedShape()
{	
	if(_actual_shape)				//	check if the shape is selected
	{	//	delete the shape from the vector

		_undo_obj.push_back(_obj[_actual_shape-1]);	//	Push to UNDO
		_obj.erase(_obj.begin()+_actual_shape-1);
		_actual_shape = 0;			//	set selected shape be nothing
	}
	else
		Error_Sound();

}
//=============================================================================
//	Clear all shapes which have exact form like selected shape if no shape 
//	selected do nothing
void Paint::ClearBySameType()
{
	int change_counter = 0;
	if(_actual_shape)				//	check if have selected shape
	{
		for(int i=0;i<(int)_obj.size();i++)
		{
			if(typeid(*_obj[_actual_shape-1]) == typeid(*_obj[i]) 
				&& _actual_shape-1 != i)
			{
				cout << "Undo obj size " << _undo_obj.size() << "\n";
				_undo_obj.push_back(_obj[i]);	//	Push to UNDO
				_obj.erase(_obj.begin() + i);	//	clear founded shape
				i--;				//	manipulation whith counter
				if(i < _actual_shape-1)
					_actual_shape--;
			}
			else if(_actual_shape-1 == i)
				_undo_obj.push_back(_obj[i]);	//	Push to UNDO
		}
		//_actual_shape -= change_counter;
		ClearSelectedShape();		//	clear selected shape
	}
	else
		Error_Sound();							//	Play sound

}

//=============================================================================
//	Clear shape by color which have selected shape
void Paint::ClearBySameColor()
{
	if(_actual_shape)				//	check if have selected shape
	{
		//	get color of selected shape
		const RgbColor tmpCol =_obj[_actual_shape-1]->GetColor();
		//	start searching
		for(int i=0;i<(int)_obj.size();i++)
		{
			//	if this shape is not selected shape and they have same color
			if(_actual_shape-1 != i && CompareColor(_obj[i]->GetColor(),tmpCol))
			{
				_undo_obj.push_back(_obj[i]);	//	Push to UNDO
				_obj.erase(_obj.begin() + i);	//	clear founded shape
				i--;				//	manipulation whith counter
				if(i < _actual_shape-1)
					_actual_shape--;
			}
			else if(_actual_shape-1 == i)
				_undo_obj.push_back(_obj[i]);	//	Push to UNDO
		}
		ClearSelectedShape();
	}	
	else
		Error_Sound();							//	Play sound
}
//=============================================================================
//	Clear Menu selection switch
void Paint::clearFromMenu(const int &id)
{
	_undo_obj.clear();
		switch(id)
		{
		case _CLR_SELECTED:			//	Clear selected shape
			ClearSelectedShape();
			break;
		case _CLR_SAME_TYPE:		//	Clear by same type
			ClearBySameType();
			break;
		case _CLR_SAME_COLOR:		//	Clear by same color
			ClearBySameColor();
			break;
		case _CLEAR_SCREEN:			//	Clear all shapes
			ClearDB();
			break;
		}
		_UndoType = _UNDO_REMOVED;	//	Set undo type
}

//=============================================================================
//	Menu to set color of drawing shape
void Paint::mnuSetColor(const int &color_value)
{
	_color_id = color_value;		//	Set new color
}


//=============================================================================
//
void Paint::mnuResize(const int &commandID)
{
	_undo_changes.clear();
	switch(commandID)	
	{
	case _GROW_SELETED:						// Grow Selected
		GrowSelectedShape();
		break;
	case _SHRINK_SELETED:					//	Shrink selected
		ShrinkSelectedShape();
		break;
	case _SAME_SIZE:						//	Set same size
		SameSizeByShape();
		break;
	}
	_UndoType = _UNDO_CHANGES;				//	Set undo type
}

//=============================================================================
//	Grow the size of selected shape
void Paint::GrowSelectedShape()
{
	const float val= _GROW_DEFAULT_SIZE;	//	set the value
	_undo_changes.clear();
	if(_actual_shape)						//	Check if selected
	{
		UndoPrepareChanges(_obj[_actual_shape-1],_actual_shape-1);
		_obj[_actual_shape-1]->IncreaseSize(val);
	}
	else
		Error_Sound();						//	Play sound

}
//=============================================================================
// Shrink  the size of selected shape
void Paint::ShrinkSelectedShape()
{
	const float val= _SHRINK_DEFAULT_SIZE;	//	set the value
	_undo_changes.clear();
	if(_actual_shape)						//	check if selected
	{
		UndoPrepareChanges(_obj[_actual_shape-1],_actual_shape-1);
		_obj[_actual_shape-1]->ShrinkSize(val);
	}
	else
		Error_Sound();						//	Play sound

}
//=============================================================================
// Set to all shapes which looks like selected shape the value of size 
//	like selected size
void Paint::SameSizeByShape()
{
	_undo_changes.clear();
	if(_actual_shape)							//	check if seleted
	{
		for(int i=0;i<(int)_obj.size();i++)
		{
			//	If the i object is same type and not the selected object
			if(typeid(*_obj[_actual_shape-1]) == typeid(*_obj[i]) 
						&& _actual_shape-1 != i)
			{
				UndoPrepareChanges(_obj[i],i);	//	Set undo		
				_obj[i]->SetSize(_obj[_actual_shape-1]->GetSize());
			}
		}
	}
	else
		Error_Sound();							//	Play sound
}

//=============================================================================
//	Idle function 
void Paint::idle()
{
	display();			//	call display function
}

//=============================================================================
//	Call back for glut mouse action
void Paint::mouseButton(const int &button,const int &state, const float &x , 
						const float &y)
{
	//	Worced on left button on UP-KEY = state == 1
	if(button == 0 && state==1 && _draw_figure)
	{
		Shape *_new_sh;

		switch(_draw_figure)
		{
		case _DOT:				//	Create dor
			_new_sh = new Dot(x,y,_colors[_color_id]);
			break;
		case _RECTANGLE:		//	Create rectangle
			_new_sh = new Rectanglle(x,y,_colors[_color_id]);
			break;
		case _EMPTY_RECTANGLE:	//	Create empty rectangle
			_new_sh = new EmptyRectangle(x,y,_colors[_color_id]);
			break;
		case _SQUARE:			//	Create square
			_new_sh = new  Square(x,y,_colors[_color_id]);	
			break;
		case _CIRCLE:			//	Circle
			_new_sh = new Circle(x,y,_colors[_color_id]);
			break;
		case _WHEEL:			//	Wheel
			_new_sh = new  Wheel(x,y,_colors[_color_id]);
			break;
		case _EMPTY_CIRCLE:		//	Create empty cicrle
			_new_sh = new EmptyCircle(x,y,_colors[_color_id]);
			break;
		case _H_LINE:			//	Horizontal line
			_new_sh = new Horizontal(x,y,_colors[_color_id]);
			break;
		case _V_LINE:			//	Vwertical line
			_new_sh = new Vertical(x,y,_colors[_color_id]);
			break;
		case _ITRIANGLE:		//	Iriangle
			_new_sh = new Itriangle(x,y,_colors[_color_id]);
			break;
		case _EQUIANGULAR:		//	Equintrangle
			_new_sh = new Equiangular(x,y,_colors[_color_id]);
			break;
		}
		
		//	Cheack if created some shape
		if(_new_sh)
		{
			//	Creating shape
			_obj.push_back(_new_sh);
			UndoPrepareRemove(_obj.size()-1);
		}
	}
}

//=============================================================================
//	Do undo for removed object/s
void Paint::UndoRemoved()
{
	for(int i=0;i<(int)_undo_obj.size();i++)
	{
		_obj.push_back(_undo_obj[i]);	//	from one vextor to work space
		_undo_obj.erase(_undo_obj.begin() + i);
		i--;							//	counter manipulations
	}	

}
//=============================================================================
//	Undo function called from menu
void Paint::Undo()
{
	//	Do what is undo type now
	switch(_UndoType)
	{
	case _UNDO_NOTHING:					//	do nothing	
		break;
	case _UNDO_REMOVE:					//	undo created object
		UndoNewObject();
		break;
	case _UNDO_CHANGES:					//	undo changes
		UndoChangesOnObjects();
		break;
	case _UNDO_SELECT:					//	undo to selection
		UndoSelection();
		break;
	case _UNDO_REMOVED:					//	undo removed
		UndoRemoved();
		break;
	}

	_UndoType = _UNDO_NOTHING;			//	reset undo to nothing

}
//=============================================================================
//	 Select Next shape
//	If shape seleted seting next shape in vector thats mean the shape 
//	which was drawed after the selected shape
//	if we got last shape we do unselect and on next selection
//	we select the first shape which was drowed
void Paint::SetNextShape()
{
	const int temp = _actual_shape;				//	temporary variable

	if(_actual_shape < (int)_obj.size())
		_actual_shape++;						//	increase selector
	else if(_actual_shape == (int)_obj.size())
		_actual_shape = 0;						//	reset selector

	UndoPrepareSelection(temp,_actual_shape);	//	Set undo
}

//=============================================================================
//	 Select Previous shape
//	If shape seleted seting prev shape in vector thats mean the shape 
//	which was drawed before the selected shape
//	if we got First shape we do unselect and on next selection
//	we select the last shape which was drowed
void Paint::SetPreviousShape()
{
	const int temp = _actual_shape;				//	temporary variable

	if(_actual_shape >0)
		_actual_shape--;						//	decrease counter
	else if(_actual_shape == 0)
		_actual_shape = (int)_obj.size();
	
	UndoPrepareSelection(temp,_actual_shape);	//	Set undo

}

//=============================================================================
//	Unselect selected shape if have selected shape
void Paint::UnSelect()
{
	const int temp = _actual_shape;

	if(_actual_shape)					//	check if the shape is selected
		_actual_shape = 0;					//	un select

	UndoPrepareSelection(temp,_actual_shape);	//	Set undo

}
//=============================================================================
//	Create undo for selction
void Paint::UndoPrepareSelection(const int &prev_sh, const int &new_sh)
{
	if(prev_sh != new_sh)	//	Manipulations for UNDO
	{
		_undoSelected	=	prev_sh;			//	set undo to prev selector
		_UndoType		=	_UNDO_SELECT;		//	set undo type
	}
}

//=============================================================================
//	Create undo for deleted  object/s
void Paint::UndoPrepareRemove(const int &id)
{
	_UndoRemove = id;
	_UndoType   = _UNDO_REMOVE;
}

//=============================================================================
//	Create undo	for delete created object
void Paint::UndoNewObject()
{
	_obj.erase(_obj.begin()+_UndoRemove);		//	just remove the object

}

//=============================================================================
//	Do undo for selection
void Paint::UndoSelection()
{
	_actual_shape = _undoSelected;				//	Undo for selection

}

//=============================================================================
//	Glut call back for keyboard
void Paint::KeyPress(unsigned char key, const float  &x, const float  &y)
{

	switch(key)
	{
		case	_CMD_UNDO:						//	UNDO
			Undo();
			break;
		case	_CMD_DELETE:					//	Delete selected object
			ClearSelectedShape();
			_UndoType = _UNDO_REMOVED;
			break;
		case	_CMD_ESC:						//	Exit
			exit(EXIT_SUCCESS);
			break;
		case	_CMD_GROW:						//	Grow selected
			GrowSelectedShape();
			_UndoType = _UNDO_CHANGES;
			break;
		case	_CMD_SHRINK:					//	Shrink selected
			ShrinkSelectedShape();
			_UndoType = _UNDO_CHANGES;
			break;
		case	_CMD_SAME_SIZE:					//	Set same size
			SameSizeByShape();
			_UndoType = _UNDO_CHANGES;
			break;
		case	_CMD_PREV:						//	Select previous
			SetPreviousShape();
			break;
		case	_CMD_NEXT:						//	Select next
			SetNextShape();
			break;
		case	_CMD_UNSELECT:					//	Unselect
			UnSelect();
			break;
		case	_CMD_REMOVE_BY_TYPE:			//	Remove shapes by type
			ClearBySameType();
			_UndoType = _UNDO_REMOVED;
			break;
		case	_CMD_REMOVE_BY_COLOR:			//	Remove by color
			ClearBySameColor();
			_UndoType = _UNDO_REMOVED;
			break;
		case	_CMD_REMOVE_ALL:				//	Remove all
			ClearDB();
			_UndoType = _UNDO_REMOVED;
			break;

	}		
}

//=============================================================================
//	Do undo for changes
void Paint::UndoChangesOnObjects()
{
	//	Start do undo for objects in undo vector
	for(int i=0;i<(int)_undo_changes.size();i++)
	{
		//	Set color and size
		_undo_changes[i].obj->SetColor(_undo_changes[i]._color);
		_undo_changes[i].obj->SetSize(_undo_changes[i]._size);
	}

	_undo_changes.clear();						//	Clear undo vector

}

//=============================================================================
//	Create undo for changes object
void Paint::UndoPrepareChanges(Shape *shape_to_save,const int &id)
{

	UndoShape _new_save;						//	Set memory	
	//	Set parameters for changed objects
	_new_save.obj		=	shape_to_save;
	_new_save._color	=	shape_to_save->GetColor();
	_new_save._size		=	shape_to_save->GetSize();
	_undo_changes.push_back(_new_save);			//	vector

}
//=============================================================================
//=============================================================================
//=============================================================================