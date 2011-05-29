#include "Grafic.h"
vector<Objects*> Grafic:: _objectsDrow;

//=============================================================================
//	Class constructor 
Grafic::Grafic()
{
	glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluOrtho2D(0, 850, 0, 600);
}

//=============================================================================
//	Dispaly function
void Grafic::Display()
{
	
	glClear(GL_COLOR_BUFFER_BIT ); 
	vector<Objects*>::const_iterator it;
	
	for(it=_objectsDrow.begin();it <_objectsDrow.end();it++)
		if((*it)->isEnabled())
			(*it)->Draw();

	glFlush() ; 
	glutSwapBuffers();

}

//=============================================================================
//	Function to add object to vector
void Grafic::addObject(Objects *newObject)
{
	_objectsDrow.push_back(newObject);

}

//=============================================================================
//	Function to to clear vector
void Grafic::ClearVector()
{
	_objectsDrow.clear();

}

//=============================================================================
//	Function to clear object from vector geted by pointer
void Grafic::clearObject(Objects *obj)
{

	const int _vec_size = (int)_objectsDrow.size();
	for(int i=0;i<_vec_size;i++)
		if(_objectsDrow[i] == obj )
		{
			_objectsDrow.erase(_objectsDrow.begin()+i);
			break;
		}


}