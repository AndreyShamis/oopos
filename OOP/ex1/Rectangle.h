


#include "shape.h"

#if !defined(_RECTANGLE_H)
#define _RECTANGLE_H

#define DEFAULT_SIZE_SH 0.1

class Rectangle :public Shape 
{
public:
	Rectangle(float x, float y, bool isEmpty);
	void Draw();
private:
	bool _isEmpty;
};

#endif  //_RECTANGLE_H
