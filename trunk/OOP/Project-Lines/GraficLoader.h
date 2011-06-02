#pragma once
#include <map>
#include "Config.h"
#include <fstream>
#include <iostream>
#include <glut.h>
#include <string.h>


using namespace std;
class GraficLoader
{
public:
	GraficLoader()
	{
		;
	}
	RGBA **getSprite(char *name)
	{
		RGBA **ret = NULL;
		map<char *,RGBA **>::iterator it;
		it =  _data.find(name);
	
		//ret = _data.find(name)->second;
		if(it != _data.end())
		{
			ret = it->second;
			return(ret);
		}
		else
		{
			char path[CHAR_MAX_STR_LEN];		//	variable for get riht path
			//	manipulation whith char
			memset(path,'\0',CHAR_MAX_STR_LEN);
			strcpy_s(path,RGBA_FOLDER);
			strcat_s(path,"\\");
			strcat_s(path,name);
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
					imageFile >> _image[i][j]._r >> _image[i][j]._g 
						>> _image[i][j]._b >> _image[i][j]._a;  
				}
			}

			_data[name] = _image;

			imageFile.close();		//close the file

			return(_data[name]);

		}
	}
	//=============================================================================
	//	return height
	int getHeight()
	{
		return(_height);
	}
	//=============================================================================
	//	return width
	int getWidth()
	{
		return(_width);
	}

private:

	//static 
	int _height;		//	height of image
	//static 
	int _width;			//	width of image
	//static 
		map <char*,RGBA **> _data;
	RGBA **_image;

};





