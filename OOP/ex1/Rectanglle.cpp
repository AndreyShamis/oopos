#include "macros.h"
#include "Rectanglle.h"

Rectanglle::Rectanglle(float x, float y, bool isEmpty)
{
	_x			= x;
	_y			= y;
	_size		= DEFAULT_SIZE_SH;
	_isEmpty	= isEmpty;
}

void Rectanglle::Draw()
{
	if(_isEmpty)
		glBegin(GL_LINES);
	else
		glBegin(GL_QUADS);//GL_POLYGON

	//cout << "rewtrtrewtrew\n";
	glColor3f(0.4f, 1.4f, 0.3f);
	glVertex2f (_x, _y);
	glVertex2f (_x + (_size * 2), _y);
	glVertex2f (_x + (_size * 2), _y - _size);
	glVertex2f (_x, _y - _size);
	glEnd();
}
