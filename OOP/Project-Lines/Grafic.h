/*

	This class provide a class for all drowable object which
	be drawed
	for more inforamtion about all function look to cpp file

	
*/

#pragma once

#include "Objects.h"
#include "Bomb.h"
#include "Bochka.h"
#include "Fire.h"
#include <vector>
#include <glut.h>
#include <typeinfo>
using namespace std ;
class Grafic
{
public:
	Grafic();
	static void Display();
	static void addObject(Objects *newObject);
	static void clearObject(Objects *obj);
	static void ClearVector();
private:
	static std::vector <Objects *> _objectsDrow; 
};
