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
//	Class constructor 
Sprite::Sprite(char* filename) {

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
		cout << "File loaded\n";
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
void Sprite::Draw(const float &cordX, float &cordY){
	glBegin(GL_POINTS);	
	int y=0,x=_width;
	for(int i=0; i<_height;i++)
	{
		x=_width;
		for(int j=0; j< _width; j++){
			if ( _image[i][j]._a >= 1)
			{
				glColor4ub(_image[i][j]._r, _image[i][j]._g, _image[i][j]._b, _image[i][j]._a);
				//glPointSize(1);//POINT_SIZE/WINDOW_HEIGHT
				glVertex2f((float)x*(POINT_SIZE/WINDOW_WIDTH) + cordX ,	((float)y*(POINT_SIZE/WINDOW_HEIGHT) + cordY));//(20*PIC_WIDTH)-//GameController::_WindowHeight
			}
			x++;
		}
		y++;
	}

	glEnd();

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
