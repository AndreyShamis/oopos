//
//
//  Generated by Andrey Shamis Ilia Gaysinski
//
//  @ Project : Paint
//  @ File Name : Paint.cpp
//  @ Date : 3/3/2011
//  @ Author : 
//
//

#include "macros.h"
#include "Paint.h"

Paint::Paint()
{
	glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluOrtho2D(0, 850, 0, 600);
}

void Paint::display()
{
	glClear(GL_COLOR_BUFFER_BIT ); 
	for(int i=0;i<(int)_obj.size();i++)
	{
		_obj[i]->Draw();
	}
	glFlush() ; 
	glutSwapBuffers();
}

void Paint::selectFromMenu(const int &id)
{
;
}

void Paint::idle()
{
	static int x;
	if(x != 10)
	{
		x = 10;
		Bar *bar;
		bar = new  Bar(120,130);

		cout << "Create \n";
		_obj.push_back(bar);
	}
}
void Paint::mouseButton(const int &button,const int &state, const float &x , const float &y)
{
	cout << "Button:" << button << " State:" << state << " X:"<<x<<" Y:"<<y << "\n";

}
void Paint::ShowMenu()
{
;
}

void Paint::DrowByStatus()
{
;
}
