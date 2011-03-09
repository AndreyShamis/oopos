


#include "shape.h"
#if !defined(_RECTANGLLE_H)
#define _RECTANGLLE_H

#define DEFAULT_SIZE_SH 0.1

class Rectanglle :public Shape
{
public:
	Rectanglle(float x, float y, bool isEmpty);
	void Draw();

private:
	bool _isEmpty;
};

#endif //_RECTANGLLE_H