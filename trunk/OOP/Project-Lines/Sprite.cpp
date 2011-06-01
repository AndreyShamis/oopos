#include "Sprite.h"

using namespace std ;

//RGBA **Sprite::_image;
//int Sprite::_height;
//int Sprite::_width;
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

Sprite::Sprite()
{
}


//=============================================================================
//	Class constructor 
Sprite::Sprite(const char* filename) {



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
		//get from the file width and hieght of image
	imageFile >> _width >> _height;

	_image  = new RGBA*[(int)_height];
	for(int i=0; i<_height; i++){
		_image[i] = new RGBA[(int)_width];
		for(int j=0; j< _width; j++){
			imageFile >> _image[i][j]._r >> _image[i][j]._g 
			>> _image[i][j]._b >> _image[i][j]._a;  
		}
	}

	
	imageFile.close();		//close the file
}

////=============================================================================
////	Draw function
//void Sprite::Draw(const float &cordX, float &cordY){
//	glBegin(GL_POINTS);	
//	int y=0,x=_width;
//	for(int i=0; i<_height;i++){
//		x=_width;
//		for(int j=0; j< _width; j++){
//			glColor4ub(_image[i][j]._r, _image[i][j]._g, _image[i][j]._b, _image[i][j]._a);
//			glVertex2f((float)x*(1.0/540) + cordX ,((float)y*(1.0/540) + cordY));//(20*PIC_WIDTH)-
//			x++;
//		}
//		y++;
//	}
//
//	glEnd();
//
//}
//=============================================================================
//	Draw function
/*
void Sprite::Draw(const float &cordX, float &cordY, Action action)
{
	int timer = 777;
	if(action == Nothing)
	{
		DrowSprite(cordX, cordY, 255);
	}
	else if(action == Appear)
	{
		for(short int alpha = 0; alpha <=255;  alpha += 17)
		{
			//timer = 999999;
			////cout <<alpha<<" ########################\n";
			DrowSprite(cordX, cordY, alpha);
			// *while(timer)
				timer --;* //

		}
	}
	else if(action == Disappear)
	{
		for(short int alpha = 255; alpha >=0;  alpha -= 17)
		{
			//timer = 999999;
			////cout <<"#########################\n";
			DrowSprite(cordX, cordY, alpha);
			/*while(timer)
				timer --;* /
		}
	}
}
	  */

//=============================================================================
//	Draw function
void Sprite::Draw(const float &cordX, float &cordY){
	glBegin(GL_POINTS);	
	int y=0,x=_width;
	for(int i=0; i<_height;i++){
		x=_width;
		for(int j=0; j< _width; j++){
			if ( _image[i][j]._a >= 1)
			{
				glColor4ub(_image[i][j]._r, _image[i][j]._g, _image[i][j]._b, 
				_image[i][j]._a);
				//glPointSize(1);//POINT_SIZE/WINDOW_HEIGHT
				glVertex2f((float)x*(POINT_SIZE/WINDOW_WIDTH) + cordX ,
					((float)y*(POINT_SIZE/WINDOW_HEIGHT) + cordY));//(20*PIC_WIDTH)-//GameController::_WindowHeight
			}
			x++;
		}
		y++;
	}

	glEnd();

}