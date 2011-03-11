//
//  @ Project : Paint
//  @ File Name : Paint.cpp
//  @ Date : 3/3/2011
//  @ Author : Andrey Shamis Ilia Gaysinski
//
//
#include "Paint.h"

//=============================================================================
//
Paint::Paint()
{
	LoadColorsToMemory();
	glMatrixMode(GL_PROJECTION);   
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
	_actual_shape = 0;					//	No shape selected
	_draw_figure = _DOT;				// Default shape 
	_color_id =_BLUE;					// Default color
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
//
void Paint::LoadColorsToMemory()
{
	_colors[_GREEN].r = 0.0;
	_colors[_GREEN].g = 1.0;
	_colors[_GREEN].b = 0.0;

	_colors[_BLACK].r = 0.0;
	_colors[_BLACK].g = 0.0;
	_colors[_BLACK].b = 0.0;

	_colors[_WHITE].r = 1.0;
	_colors[_WHITE].g = 1.0;
	_colors[_WHITE].b = 1.0;

	_colors[_RED].r = 1.0;
	_colors[_RED].g = 0.0;
	_colors[_RED].b = 0.0;

	_colors[_BLUE].r = 0.0;
	_colors[_BLUE].g = 0.0;
	_colors[_BLUE].b = 1.0;

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
	glClear(GL_COLOR_BUFFER_BIT ); 

	for(int i=0;i<(int)_obj.size();i++)
	{
		if( i == _actual_shape-1)
		{	
			const RgbColor temp = _obj[i]->GetColor();
			_obj[i]->SetColor(_colors[_GRAY]);
			_obj[i]->Draw();
			_obj[i]->SetColor(temp);
		}
		else
			_obj[i]->Draw();
	}
	glFlush() ; 
	glutSwapBuffers();


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
	_draw_figure = id;
	//if(id > 100)
	//{
		switch(_draw_figure)
		{
		case _PREV_SHAPE:
			SetPreviousShape();
			break;
		case _NEXT_SHAPE:
			SetNextShape();
			break;	
		case _REMOVE_MARK:
			UnSelect();
			break;	
		case _UNDO:
			Undo();
			break;	
		case _EXIT_PROGRAM:
			//ClearDB();
			exit(EXIT_SUCCESS);
			break;
		}
	//}

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
			if(typeid(*_obj[_actual_shape-1]) == typeid(*_obj[i]) && _actual_shape-1 != i)
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
		Error_Sound();

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
		Error_Sound();
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
		Error_Sound();

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
		Error_Sound();

}
//=============================================================================
// Set to all shapes which looks like selected shape the value of size 
//	like selected size
void Paint::SameSizeByShape()
{
	_undo_changes.clear();
	if(_actual_shape)						//	check if seleted
	{
		for(int i=0;i<(int)_obj.size();i++)
		{
			if(typeid(*_obj[_actual_shape-1]) == typeid(*_obj[i]) && _actual_shape-1 != i)
			{
				UndoPrepareChanges(_obj[i],i);			
				_obj[i]->SetSize(_obj[_actual_shape-1]->GetSize());

			}
		}
	}
	else
		Error_Sound();
}

//=============================================================================
//
void Paint::idle()
{
	display();
}

//=============================================================================
//
void Paint::mouseButton(const int &button,const int &state, const float &x , 
						const float &y)
{
	//cout << "Button:" << button << " State:" << state << " X:"<<x<<" Y:"<<y << "\n";
	if(button == 0 && state==1 && _draw_figure && _draw_figure < 100)
	{
		Shape *_new_sh;
		switch(_draw_figure)
		{
		case _DOT:
			_new_sh = new Dot(x,y,_colors[_color_id]);
			break;
		case _RECTANGLE:
			_new_sh = new Rectanglle(x,y,_colors[_color_id]);
			break;
		case _EMPTY_RECTANGLE:
			_new_sh = new EmptyRectangle(x,y,_colors[_color_id]);
			break;
		case _SQUARE:
			_new_sh = new  Square(x,y,_colors[_color_id]);	
			break;
		case _CIRCLE:
			_new_sh = new Circle(x,y,_colors[_color_id]);
			break;
		case _WHEEL: 
			_new_sh = new  Wheel(x,y,_colors[_color_id]);
			break;
		case _EMPTY_CIRCLE:
			_new_sh = new EmptyCircle(x,y,_colors[_color_id]);
			break;
		case _H_LINE:
			_new_sh = new Horizontal(x,y,_colors[_color_id]);
			break;
		case _V_LINE:
			_new_sh = new Vertical(x,y,_colors[_color_id]);
			break;
		case _ITRIANGLE:
			_new_sh = new Itriangle(x,y,_colors[_color_id]);
			break;
		case _EQUIANGULAR:
			_new_sh = new Equiangular(x,y,_colors[_color_id]);
			break;
		}
		
		if(_new_sh)
		{
			_obj.push_back(_new_sh);
			UndoPrepareRemove(_obj.size()-1);
		}
	}
}

//=============================================================================
//
void Paint::UndoRemoved()
{
	for(int i=0;i<(int)_undo_obj.size();i++)
	{
		_obj.push_back(_undo_obj[i]);
		_undo_obj.erase(_undo_obj.begin() + i);
		i--;
	}	

}
//=============================================================================
//
void Paint::Undo()
{
	switch(_UndoType)
	{
	case _UNDO_NOTHING:
		break;
	case _UNDO_REMOVE:
		UndoNewObject();
		break;
	case _UNDO_CHANGES:
		UndoChangesOnObjects();
		break;
	case _UNDO_SELECT:
		UndoSelection();
		break;
	case _UNDO_REMOVED:
		UndoRemoved();

		break;
	}
	_UndoType = _UNDO_NOTHING;
}
//=============================================================================
//	 Select Next shape
//	If shape seleted seting next shape in vector thats mean the shape 
//	which was drawed after the selected shape
//	if we got last shape we do unselect and on next selection
//	we select the first shape which was drowed
void Paint::SetNextShape()
{
	const int temp = _actual_shape;

	if(_actual_shape < (int)_obj.size())
		_actual_shape++;
	else if(_actual_shape == (int)_obj.size())
		_actual_shape = 0;

	UndoPrepareSelection(temp,_actual_shape);
}

//=============================================================================
//	 Select Previous shape
//	If shape seleted seting prev shape in vector thats mean the shape 
//	which was drawed before the selected shape
//	if we got First shape we do unselect and on next selection
//	we select the last shape which was drowed
void Paint::SetPreviousShape()
{
	const int temp = _actual_shape;

	if(_actual_shape >0)
		_actual_shape--;
	else if(_actual_shape == 0)
		_actual_shape = (int)_obj.size();
	
	UndoPrepareSelection(temp,_actual_shape);

}

//=============================================================================
//	Unselect selected shape if have selected shape
void Paint::UnSelect()
{
	const int temp = _actual_shape;

	if(_actual_shape)				//	check if the shape is selected
		_actual_shape = 0;			//	un select

	UndoPrepareSelection(temp,_actual_shape);

}
//=============================================================================
//
void Paint::UndoPrepareSelection(const int &prev_sh, const int &new_sh)
{
	if(prev_sh != new_sh)	//	Manipulations for UNDO
	{
		_undoSelected	=	prev_sh;
		_UndoType		=	_UNDO_SELECT;
	}
}

//=============================================================================
//
void Paint::UndoPrepareRemove(const int &id)
{
	_UndoRemove = id;
	_UndoType   = _UNDO_REMOVE;
}

//=============================================================================
//
void Paint::UndoNewObject()
{
	_obj.erase(_obj.begin()+_UndoRemove);

}

//=============================================================================
//
void Paint::UndoSelection()
{
	_actual_shape = _undoSelected;

}

//=============================================================================
//
void Paint::KeyPress(unsigned char key, const float  &x, const float  &y)
{
	//cout << "Key " << key << " x : " << x << " y:" << y << "\n";
	//cout << "Key INT " << (int)key << "\n";
	switch(key)
	{
		case	_CMD_UNDO:
			Undo();
			break;
		case	_CMD_DELETE:
			ClearSelectedShape();
			_UndoType = _UNDO_REMOVED;
			break;
		case	_CMD_ESC:
			exit(EXIT_SUCCESS);
			break;
		case	_CMD_GROW:
			GrowSelectedShape();
			_UndoType = _UNDO_CHANGES;
			break;
		case	_CMD_SHRINK:
			ShrinkSelectedShape();
			_UndoType = _UNDO_CHANGES;
			break;
		case	_CMD_SAME_SIZE:
			SameSizeByShape();
			_UndoType = _UNDO_CHANGES;
			break;
		case	_CMD_PREV:
			SetPreviousShape();
			break;
		case	_CMD_NEXT:
			SetNextShape();
			break;
		case	_CMD_UNSELECT:
			UnSelect();
			break;
		case	_CMD_REMOVE_BY_TYPE:
			ClearBySameType();
			_UndoType = _UNDO_REMOVED;
			break;
		case	_CMD_REMOVE_BY_COLOR:
			ClearBySameColor();
			_UndoType = _UNDO_REMOVED;
			break;
		case	_CMD_REMOVE_ALL:
			ClearDB();
			_UndoType = _UNDO_REMOVED;
			break;

	}		
}

//=============================================================================
//
void Paint::UndoChangesOnObjects()
{
	for(int i=0;i<(int)_undo_changes.size();i++)
	{
		//cout << "_size: " << _undo_changes[i]._size <<" ID" << _undo_changes[i]._id_obj << "\n";
		_undo_changes[i].obj->SetColor(_undo_changes[i]._color);
		_undo_changes[i].obj->SetSize(_undo_changes[i]._size);
	}
	_undo_changes.clear();
}

//=============================================================================
//
void Paint::UndoPrepareChanges(Shape *shape_to_save,const int &id)
{

	UndoShape _new_save;
	_new_save.obj		=	shape_to_save;
	_new_save._color	=	shape_to_save->GetColor();
	_new_save._size		=	shape_to_save->GetSize();
	//cout << "ID " << _new_save._id_obj << " Size :" << _new_save._size << "\n";
	_undo_changes.push_back(_new_save);

}
//=============================================================================
//=============================================================================
//=============================================================================