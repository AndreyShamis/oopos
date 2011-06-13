#include "Sprite.h"


using namespace std ;

//RGBA **Sprite::_image;
//int Sprite::_height;
//int Sprite::_width;
//GraficLoader Sprite::_temp;
Sprite::Sprite()
{
}
//=============================================================================
//
void Sprite::setSelected()
{
	_selected = true;

}
//=============================================================================
//
void Sprite::unSelect()
{
	_selected = false;
}
//=============================================================================
//
void Sprite::StartTurnOff()
{
	_turnOff = true;
	_alpha = 250;
}
//=============================================================================
//
void Sprite::StartTurnOn()
{
	_born = true;
	_alpha = 2;
}




//=============================================================================
//	Class constructor 
Sprite::Sprite(char* filename) {
	_turnOff = false;
	_born = false;
	//_image = _temp.getSprite(filename);
	//_width = _temp.getWidth();
	//_height = _temp.getHeight();
	
	char path[CHAR_MAX_STR_LEN];		//	variable for get riht path
	//	manipulation whith char
	memset(path,'\0',CHAR_MAX_STR_LEN);
	strcpy_s(path,RGBA_FOLDER);
	strcat_s(path,"\\");
	strcat_s(path,filename);
	// and manipulation and open file
	ifstream imageFile(path);		//open a file

	if(!imageFile.is_open())
	{
		cout << "Can`t load file " << path << "\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "+";
	}
		//get from the file width and hieght of image
	imageFile >> _width >> _height;

	_image  = new RGBA*[(int)_height];
	for(int i=0; i<_height; i++){
		_image[i] = new RGBA[(int)_width];
		for(int j=0; j< _width; j++){
			imageFile >> _image[i][j]._r >> _image[i][j]._g >> _image[i][j]._b >> _image[i][j]._a;  
		}
	}

	imageFile.close();		//close the file
	
}

//=============================================================================
//	Draw function
void Sprite::Draw(const float &cordX, float &cordY)
{

	if(_turnOff &&_alpha >0)
		_alpha-= 15;
	
	if(_turnOff && _alpha < 0)
		_alpha = 0;

	if(_born &&_alpha < 230)
		_alpha+= 15;
	
	if(_born && _alpha > 220)
		_born = false;

	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_ALPHA);

	//glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);	

	int y=0,x=_width;
	for(int i=0; i<_height;i++)
	{
		x=_width;
		for(int j=0; j< _width; j++){
			if ( _image[i][j]._a >= 1)
			{
				if(_selected && !_turnOff && !_born)
					glColor4ub(_image[i][j]._r, _image[i][j]._g, _image[i][j]._b, 120);
				else if(!_turnOff && !_born)
					glColor4ub(_image[i][j]._r, _image[i][j]._g, _image[i][j]._b, _image[i][j]._a);
				else
					glColor4ub(_image[i][j]._r, _image[i][j]._g, _image[i][j]._b,_alpha);

				glVertex2f((float)x*(POINT_SIZE/WINDOW_WIDTH) + cordX ,	((float)y*(POINT_SIZE/WINDOW_HEIGHT) + cordY));
			}
			x++;
		}
		y++;
	}
	
	glEnd();
	
//int screenWidth, screenHeight, windowWidth, windowHeight;

//screenWidth = glutGet(GLUT_SCREEN_WIDTH);
//screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
//windowWidth = glutGet(GLUT_WINDOW_WIDTH);
//windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
//	cout << screenWidth << " " << screenHeight << " " <<  windowWidth << " " << windowHeight << "\n";
}

//=============================================================================
//	return height
int Sprite::getHeight()
{
	return(_height);
}
//=============================================================================
//	return width
int Sprite::getWidth()
{
	return(_width);
}
