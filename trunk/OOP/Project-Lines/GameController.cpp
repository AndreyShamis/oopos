#include "GameController.h"

#include <math.h>


#define _EASY_REDISPLAY 10000
#define _FAST_REDISPLAY 100
//=============================================================================
// singletone
GameController *GameController::_instance = NULL;
// initialite static virables
int						GameController::_WindowHeight = WINDOW_HEIGHT;
int						GameController::_WindowWidth  = WINDOW_WIDTH;

int						GameController::_BallCounter = 0;
unsigned int			GameController::_PostRedisplay=_FAST_REDISPLAY;

Board					GameController::gameBoard(-1.0f,0.f);
bool					GameController::_canAddBalls;
unsigned int			GameController::_StartCell;
unsigned int			GameController::_EndCell;
vector <Ball>			GameController::_newBalls;
//vector <Ball>			GameController::_ballsMap;
vector <BallColor>		GameController::_AllColors;
FMOD::Sound*			GameController::_sounds[MAX_SOUNDS];
Graph<Floor>			GameController::_floors;
FMOD::System*			GameController::_system;
map<vector<int>, Ball>	GameController::_BallMap;
//map<vector<int> ,*Floor>GameController::_FloorsMap;
vector<int>				GameController::_coords;
vector<Ball>			GameController::_Balls;
bool					GameController::_BallEraseBoard[_BOARD_SIZE_X][_BOARD_SIZE_Y];
int						GameController::PrevFounded = 0;
int						GameController::GamePoints = 0;


//=============================================================================
//	Function wich prepare new game parameters such game points new balls
//	and other
void GameController::RealodGame()
{

	_BallMap.clear();				//	cleare map
	//	Create graph iterator
	Graph<Floor>::GraphIterator<Floor> it(_floors);
	for(;it != it.end() ;it++)
	{						//	for each graph entry set back edges for BFS
		_floors.tempDetach((*it)->getID(),false);
		(*it)->setBalled(false);	//	Set not balls
	}
	_BallCounter	= 0;			//	balls on board	
	GamePoints		= 0;			//	game points
	CreateBall();					//	Create new balls
	PutBall();						//	Put them on Board
	CreateBall();					//	Craeate balls for next iteration
}
//=============================================================================
// Here is the function that print taxt at the window of the game
// get coordinats and color type
void GameController::glutPrint(float x, float y, char* text, float r, float g, 
							   float b, float a) 
{ 
	// for more information see google. . .
	if(!text || !strlen(text))return;
	bool blending = false; 
	if(glIsEnabled(GL_BLEND)) blending = true; 
	glEnable(GL_BLEND); 
	glColor4f(r,g,b,a); 
	glRasterPos2f(x,y); 
	while (*text) { 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text); 
		text++; 
	} 
	if(!blending) glDisable(GL_BLEND); 
} 

//=============================================================================
//	Function call back which used in glut
//	From this function you can exit from the game
//	And Also you can Reload Game= Get new Game board
void GameController::KeyPress(unsigned char key, int x, int y)
{
	if(key == 'q')
		exit(EXIT_SUCCESS);
	else if(key == 'n')
		RealodGame();
}

//=============================================================================
/*
 *		Function wich random create new balls and put them into temp vector
 *	and then they be taken from the temp vector
 */
void GameController::CreateBall()
{
	int					i	= 0;			//	temp variable
	const int newBallsSize	= rand()%2+1;   //	number of new balls
	const float startX		= 0.8225;		//	start coordinates
	float		startY		= 0.183;		//	start coordinates

	//	Check if have to put ball
	while (i <=newBallsSize)
	{
		int startRand = 0;					//	temp parameters
		int stopRand = 7;					//	temp parameters
		bool giveSpecial = false;

		//	Here is few block of seting parameters for random
		if(rand()%6 == 3)					//	rand multicolor ball and bomb
			giveSpecial = true;				//	temp parameters

		if(rand()%7 < rand()%3)
		{									//	Simple color section
			startRand = 7;					//	temp parameters
			stopRand = 10;					//	temp parameters
		}
		else if(giveSpecial && rand()%3 < rand()%2)
		{									//	multi color section
			startRand = 10;					//	temp parameters
			stopRand = 12;					//	temp parameters
		}

		//	Here is section for get random ball	
		const int newBallColor = rand()%(stopRand -startRand) + startRand;

		Ball tempBall = _Balls[newBallColor];	//	create-copy ball

		tempBall.setX(startX);				//	set parameters of new ball
		tempBall.setY(startY);				//	set parameters of new ball
		tempBall.setNaturalX(-1);			//	set parameters of new ball
		tempBall.setNaturalY(-1);			//	set parameters of new ball

		_newBalls.push_back(tempBall);		//	put to ProBalls DB

		i++;								//	increase counter
		startY+=0.1;						//	increase new coordinate
	}
}
//=============================================================================
//	Function wich toke the balls crated before and put them ob board
void GameController::PutBall()
{
	float	startX = 0.2025,			//	start coordinate parameters
			startY = 0.063;				//	start coordinate parameters	
	const float offsetX = FLOOR_SIZE/_WindowWidth,	//	Picture corection
				offsetY = FLOOR_SIZE/_WindowHeight;	//	Picture corection
	int RandSize = 0;					//	temp variable

	//	While have balls on ProGame Vector of balls and can put balls
	while(_newBalls.size() && _BallCounter < (int)_floors.countNodes() )
	{
		RandSize=(int)_floors.countNodes()-_BallCounter;//	get random postion
		Graph<Floor>::GraphIterator<Floor> it(_floors);	//	Get iterator of graph
		//	For each cell check if can put ball there
		for(;it != it.end() &&  _newBalls.size();it++)
		{
			if(!(*it)->getBalled() && rand()%RandSize == 0)
			{		
				//	Coordiante setting
				_newBalls[0].setX((*it)->getX());		//	set grafiv position
				_newBalls[0].setY((*it)->getY()); 		//	set grafic position
				_newBalls[0].setNaturalX((*it)->getNaturalX());	//	set position
				_newBalls[0].setNaturalY((*it)->getNaturalY());	//	set position
				_newBalls[0].setID((*it)->getID());	//	set ball id like cell id
				//	Prepare put ball into map
				setVecOfCoords((*it)->getNaturalX(),(*it)->getNaturalY());  // STL
				//	Put into map
				_BallMap.insert(pair<vector<int>,Ball>(_coords,_newBalls[0]));
				//	erase ball from Progame vector
				_newBalls.erase(_newBalls.begin()) ;

				(*it)->setBalled(true);				//	update setings of cell
				_floors.tempDetach((*it)->getID(),true);

				_BallCounter++;						//	increase ball counter
			}
		}
	}

	if(_BallCounter == (int)_floors.countNodes())
		cout << "Game OVER\n";
	else
		playSound(Appear);	
}

//=============================================================================
//	Function wich do all postmoved operations
//	The function called to another function find by diogonale vericale
//	Puting temp data into bool variable wich provaide note for balls
//	wich need remove from table game
void GameController::BumBum()
{
	int counter_Balls = 0;					//	temp variable

	//	Prepare the boolean data for new action
	memset(_BallEraseBoard,0,sizeof(_BallEraseBoard)*sizeof(bool));
	checkRowsAndCols();						//	check rows and cols
	checkDiagonals();						//	check diagonals

	//	For each cell on board game - each bool element seted
	for(int i = 0; i<_BOARD_SIZE_X;i++)
	{
		for(int j=0; j<_BOARD_SIZE_Y;j++)
		{
			if(_BallEraseBoard[i][j])		//	if bool seted
			{
				setVecOfCoords(i,j);		//	set temp parameters of map
				//	Cells oprations BFS fix- need
				_floors.tempDetach(_BallMap[_coords].getID(),false);//	put back ages
				_floors.getData(_BallMap[_coords].getID())->setBalled(false);
				_BallMap.erase(_coords);	//	erase ball
				counter_Balls++;			//	increase counter of fiunded balls
			}
		}
	}

	//	Game points manipulation
	if(counter_Balls>0)
		PrevFounded++;						//	if previous move you get balls
	else									//	if previuos maove you not success find
		PrevFounded = 0;

	GamePoints+=PrevFounded*counter_Balls*50;	//	update agame points

	//OrangeRedBall Mixed1(0,0,0,0), Mixed2(0,0,0,0);
	//BlackBall black1(0,0,0,0), black2(0,0,0,0);
	//if(Mixed1 == Mixed2)
	//	cout << "NISHTIAK1\n";
	//else
	//	cout << "HUIOVA1\n";
}

//=============================================================================
//
void GameController::checkDiagonals()
{
	for(short int i = 4; i >=0; i--)
	{
		updDiagonLftDownExis(i, Row);
		updDiagonLftDownExis(i, Column);
		updDiagonLftDownExis(i, BackRow);
		updDiagonLftDownExis(i, BackColumn);
	}
}


//=============================================================================
//
void GameController::checkRowsAndCols()
{
	for(short int i = 0; i < _BOARD_SIZE_X; i++)
	{
		short int matchCounter = 1;
		short int start = 0;

		updateLineExistence(i, matchCounter, start, Row);

		if(matchCounter >= 5)
			updateBallEraseBoard(i, matchCounter, start, Row);

		matchCounter = 1;
		start = 0;

		updateLineExistence(i, matchCounter, start, Column);

		if(matchCounter >= 5)
			updateBallEraseBoard(i, matchCounter, start, Column);
	}
}

//=============================================================================
//
void GameController::updDiagonLftDownExis(const short int &i, Direction direc)
{
	short int start = 0; 
	short int matchCounter = 1;
	map<vector<int>,Ball>::const_iterator it1,it2;

	while((start + matchCounter) < (9-i))
	{
		if(direc == Row)// start x begen from 0
		{
			setVecOfCoords(i+start, start);
			it1 = _BallMap.find(_coords);
			setVecOfCoords(i+start+matchCounter, start + matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else if(Column)
		{
			setVecOfCoords(start, i+start);
			it1 = _BallMap.find(_coords);
			setVecOfCoords(start + matchCounter, i+start+matchCounter);
			it2 = _BallMap.find(_coords);
		}
		/*else if (BackRow)
		{
			setVecOfCoords(8-i-start, start);
			it1 = _BallMap.find(_coords);
			setVecOfCoords(8-i-start-matchCounter, start + matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else
		{
			setVecOfCoords(8-start, i+start);
			it1 = _BallMap.find(_coords);
			setVecOfCoords(8-start-matchCounter, i+start+matchCounter);
			it2 = _BallMap.find(_coords);
		}*/




		if(ballsComp(it1,it2))
		{
			matchCounter++;
		}
		else
		{
			if (matchCounter >= 5)
				break;

			start += matchCounter;
			matchCounter = 1;
		}
	}

	if (matchCounter >= 5)
	{
		short int end = start + matchCounter;
		while(start != end)
		{
			if(direc == Row)
				_BallEraseBoard[i+start][start] = true;

			else if(direc == Column)
				_BallEraseBoard[start][i+start] = true;

			/*else if(direc == BackRow)
				_BallEraseBoard[8-i-start][start] = true;


			else
				_BallEraseBoard[8-start][i+start] = true;*/


			start++;
		}
	}
}
			 






//=============================================================================
//
void GameController::updateLineExistence(const short int &i,
										 short int &matchCounter,
										 short int &start,Direction direc)
{
	map<vector<int>,Ball>::const_iterator it1,it2;

	while((start + matchCounter) < 9)// && start < 6)
	{
		if(direc == Row)
		{
			setVecOfCoords(i, start);
			it1 = _BallMap.find(_coords);
			setVecOfCoords(i, start + matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else
		{
			setVecOfCoords(start, i);
			it1 = _BallMap.find(_coords);
			setVecOfCoords(start + matchCounter, i);
			it2 = _BallMap.find(_coords);
		}

		if(ballsComp(it1,it2))
		{
			matchCounter++;
		}
		else
		{
			if (matchCounter >= 5)
				return;

			start += matchCounter;
			matchCounter = 1;
		}
	}
}

//=============================================================================
//
bool GameController::ballsComp(map<vector<int>,Ball>::const_iterator &b1,
							   map<vector<int>,Ball>::const_iterator &b2)
{
	if (b1 == _BallMap.end() || b2 == _BallMap.end())
		return false;

	else if (b1->second == b2->second)
		return true;

	else
		return false;
}

//=============================================================================
//
void GameController::updateBallEraseBoard(const short int &location,
										  const short int &matchCounter,
										  const short int &start,
										  Direction direc)
{
	for(int index = start; index < start + matchCounter; index++)
	{
		if(direc == Row)
			_BallEraseBoard[location][index] = true;

		else
			_BallEraseBoard[index][location] = true;
	}
}

//=============================================================================
//	Function that load soumd files.
void GameController::loadSounds()
{
	if(FMOD::System_Create(&_system))
		printErrorMSG("System_Create");

	// load sound
	_system->setOutput(FMOD_OUTPUTTYPE_DSOUND );
	_system->init(32, FMOD_INIT_NORMAL, 0);

	if(	_system->createSound("Sounds/appear.mp3", NULL, NULL, &_sounds[0])	||
		_system->createSound("Sounds/disappear.mp3", NULL, NULL, &_sounds[1])||
		_system->createSound("Sounds/explosion.mp3", NULL, NULL, &_sounds[3])||
		_system->createSound("Sounds/error.mp3", NULL, NULL, &_sounds[4])	||
		_system->createSound("Sounds/double_bonus.mp3", FMOD_LOOP_NORMAL, NULL,&_sounds[2])||
		_system->createSound("Sounds/cautious-path.mp3", NULL, NULL,&_sounds[5]))

		printErrorMSG("createSound");
}

//=============================================================================
//	Function that print Error messeges
void GameController::printErrorMSG(char *sentence)
{
	cout << "Function: " << sentence << "fail\n";
	exit(EXIT_FAILURE);
}
//=============================================================================
//	Function is used in loading class
void GameController::playSound(SoundsName soundName)
{
	FMOD::Channel* channel = 0; 

	switch(soundName){

		case Appear:		_system->playSound(FMOD_CHANNEL_FREE, _sounds[0], 
															false, &channel); 	
							break;
		case Disappear:		_system->playSound(FMOD_CHANNEL_FREE, _sounds[1], 
															false, &channel); 	
							break;
		case double_bonus:	_system->playSound(FMOD_CHANNEL_FREE, _sounds[2], 
															false, &channel); 	
							break;
		case explosion:		_system->playSound(FMOD_CHANNEL_FREE, _sounds[3], 
															false, &channel); 
							break;
		case BackGround:		_system->playSound(FMOD_CHANNEL_FREE, _sounds[5], 
								false, &channel); 
							break;
		case error:			_system->playSound(FMOD_CHANNEL_FREE, _sounds[4], 
															false, &channel); 
							break;
	}
}
//=============================================================================
//	Function that load balls objects
void GameController::loadBalls()
{
	float x=0;
	float y=0;
	int nutX=-1;
	int nutY=-1;

	GreenBall		greenBall(x,y,nutX,nutY);
	WhiteBall		whiteBall(x,y,nutX,nutY);
	BlackBall		blackBall(x,y,nutX,nutY);
	YellowBall		yellowBall(x,y,nutX,nutY);
	OrangeBall		orangeBall(x,y,nutX,nutY);
	BlueBall		blueBall(x,y,nutX,nutY);
	RedBall			redBall(x,y,nutX,nutY);
	GreenYellowBall greenYellowBall(x,y,nutX,nutY);
	OrangeRedBall	orangeRedBall(x,y,nutX,nutY);
	WhiteBlueBall	whiteBlueBall(x,y,nutX,nutY);
	MixedBall		mixedBall(x,y,nutX,nutY);
	BombBall		bombBall(x,y,nutX,nutY);

	_Balls.push_back(greenBall);
	_Balls.push_back(whiteBall);
	_Balls.push_back(blackBall);
	_Balls.push_back(yellowBall);
	_Balls.push_back(orangeBall);
	_Balls.push_back(blueBall);
	_Balls.push_back(redBall);
	_Balls.push_back(greenYellowBall);
	_Balls.push_back(orangeRedBall);
	_Balls.push_back(whiteBlueBall);
	_Balls.push_back(mixedBall);
	_Balls.push_back(bombBall);
}
//=============================================================================
void GameController::loadFloors()
{
	float startX = 0.2025;
	float startY = 0.063;

	unsigned int prev_vertex = 0;
	const float offsetX = FLOOR_SIZE/_WindowWidth;
	const float offsetY = FLOOR_SIZE/_WindowHeight;

	vector <unsigned int> _prevLine;
	vector <unsigned int> _thisLine;
	Floor tempFloor(startX,startY,0,0);

	for (int i=0;i<_BOARD_SIZE_X;i++)
	{
		prev_vertex = 0;
		for (int j=0;j<_BOARD_SIZE_Y;j++)
		{
			//Floor newFloor(startX,startY,i,j);
			Floor newFloor = tempFloor;
			newFloor.setX(startX);
			newFloor.setY(startY);
			newFloor.setNaturalX(i);
			newFloor.setNaturalY(j);

			unsigned int newVert = _floors.addVertex(newFloor);
			_floors.getData(newVert)->setID(newVert);

			_thisLine.push_back(newVert);
			if(i>0)
				_floors.addEdge(_prevLine[j],_thisLine[j]);
			if(prev_vertex)
				_floors.addEdge(prev_vertex,newVert);
			prev_vertex = newVert;

			startY +=offsetY;
		}
		startY =0.063;
		startX +=offsetX;
		_prevLine.clear();
		_prevLine = _thisLine;
		_thisLine.clear();
	}
}




//=============================================================================
//	Function is used in loading class
void GameController::LoadGame()
{
	srand(time((int)NULL));


	loadSounds();
	loadBalls();
	loadFloors();

	playSound(BackGround);
	CreateBall();
	PutBall();
	CreateBall();
}

//=============================================================================
void GameController::FloorDoAllSimple()
{
	Graph<Floor>::GraphIterator<Floor> itSimple(_floors);
	for(;itSimple != itSimple.end() ;itSimple++)
	{
		(*itSimple)->setFloorType(Simple);
	}

}
//=============================================================================
void GameController::mouseMove(int x,int y)//////////////////////////////
{

	if(_StartCell>0)
	{
	
		const float xPos = ((float)x)/((float)(WINDOW_WIDTH));
		const float yPos =1.0f- ((float)y)/((float)(WINDOW_HEIGHT));

		const float CELL_SIZE_X = FLOOR_SIZE/_WindowWidth;
		const float CELL_SIZE_Y = FLOOR_SIZE/_WindowHeight;
		
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		int _prevEndCell = _EndCell;
		_EndCell = 0;
		for(;it != it.end() ;it++)
		{
			float _X = (*it)->getX();
			float _Y = (*it)->getY();
			if(_X <= xPos-CELL_SIZE_X  && (_X+CELL_SIZE_X ) > xPos-CELL_SIZE_X 
				&&  _Y <= yPos && _Y+CELL_SIZE_Y> yPos)
			{
				if(!(*it)->getBalled())
				{
					_EndCell = (*it)->getID();
					_canAddBalls = true;
				}
				else
				{
					_EndCell = 0;
					_canAddBalls = false;
				}
				break;
			}
		}
		
		FloorDoAllSimple();
		if( _EndCell && _StartCell != _EndCell)
		{
			//cout << "Enter to check\n";

			_floors.tempDetach(_StartCell,false);
			vector<int> _bfsVec = _floors.getVectorOfSimplePath(_StartCell,_EndCell);
			
			int _inVec=0;

			
			_canAddBalls = false;
			int vect_Size =	   (int)_bfsVec.size();
			for (int i=0;i<vect_Size;i++)
			{
				if(_bfsVec[i] == _EndCell)
				{
					_inVec = _bfsVec[i];
					_canAddBalls = true;			
					break;
				}
			}

			//FloorDoAllSimple();
			//_inVec = _EndCell;
			while(_inVec > 0)
			{
				_floors.getData(_inVec)->setFloorType(Selected);
				_inVec = _floors.getBfsDfsFather(_inVec);
			}
			_floors.tempDetach(_StartCell,true);

			
		}
	}	//	End condition if _Start selected
}
//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)/////
	{
	float xPos = ((float)x)/((float)(WINDOW_WIDTH));
	float yPos = ((float)y)/((float)(WINDOW_HEIGHT));
	yPos = 1.0f-yPos;
	vector <int> tempCoords;

	if(state == 0)
	{

		_PostRedisplay = _FAST_REDISPLAY;
		static float CELL_SIZE_X = FLOOR_SIZE/_WindowWidth;
		static float CELL_SIZE_Y = FLOOR_SIZE/_WindowHeight;
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		for(;it != it.end() ;it++)
		{
			float _X = (*it)->getX();
			float _Y = (*it)->getY();
			if(_X <= xPos-CELL_SIZE_X  && (_X+CELL_SIZE_X ) > xPos-CELL_SIZE_X 
				&&  _Y <= yPos && _Y+CELL_SIZE_Y> yPos)
			{
				//(*it)->setFloorType(Selected);
				
				if((*it)->getBalled())
					_StartCell = (*it)->getID();
				else
				   _StartCell =0;
				//cout << "Founded Start CELL : " << _StartCell  << "\n";
				break;
			}
		}	
		//cout << "X:" << xPos << " --Y:" << yPos << "\n";
	}
	else if(state == 1)
	{

		FloorDoAllSimple();
		if(_canAddBalls && _StartCell != _EndCell && _EndCell >0 && _StartCell>0)
		{
			map<vector<int> ,Ball>::iterator itb = _BallMap.begin();

			for(;itb != _BallMap.end() ;itb++)
			{
				if( ((*itb).second).getID() == _StartCell)
				{	
					//setVecOfCoords(((*itb).second).getNaturalX(),((*itb).second).getNaturalY()); // chenging key STL

					setVecOfCoords(_floors.getData(_EndCell)->getNaturalX(),_floors.getData(_EndCell)->getNaturalY());	 // chenging key STL

					_BallMap[_coords] = _BallMap[(*itb).first];

					_BallMap[_coords].setX(_floors.getData(_EndCell)->getX());
					_BallMap[_coords].setY(_floors.getData(_EndCell)->getY());
					_BallMap[_coords].setNaturalX(_floors.getData(_EndCell)->getNaturalX());
					_BallMap[_coords].setNaturalY(_floors.getData(_EndCell)->getNaturalY());
					_BallMap[_coords].setID(_EndCell);

					cout << _floors.getData(_EndCell)->getNaturalX() << " " << _floors.getData(_EndCell)->getNaturalY() << "\n";

					_floors.tempDetach(_StartCell,false);
					_floors.tempDetach(_EndCell,true);
					_floors.getData(_EndCell)->setBalled(true);
					_floors.getData(_StartCell)->setBalled(false);

					_BallMap.erase(itb);


					//_BallMap.insert(pair<vector<int>,Ball>(_coords,tempBall));
					BumBum();
					PutBall();
					CreateBall(); 
					break;
				}

			}
			//------------------------------------------
		}
		else 
			playSound(error);
		_StartCell = 0;
		_EndCell = 0;
		_PostRedisplay = _EASY_REDISPLAY;
	}
}


//=============================================================================
//	
void GameController::setVecOfCoords(const int &coordX, const int &coordY)
{
	if(_coords.size())
	{
		_coords[0]= coordX;
		_coords[1]= coordY;
	}
	else
	{
		_coords.push_back(coordX);
		_coords.push_back(coordY);
	}
}



//=============================================================================
//	Dispaly function
void GameController::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	gameBoard.Draw();							//	Draw background board

	//	Here we drawing the cells of board
	Graph<Floor>::GraphIterator<Floor> it(_floors);
	for(;it != it.end() ;it++)
		(*it)->Draw();							//	drawe

	//	Start work with map of balls and draw balls loacated on board
	map<vector<int> ,Ball>::iterator itb = _BallMap.begin();
	for(;itb != _BallMap.end() ;itb++)
		((*itb).second).Draw();					//	draw

	//	Here is block of code wich provide animation on drag and drop
	if(_StartCell > 0 && _EndCell > 0 && _StartCell != _EndCell && _canAddBalls)
	{
		//	Get ball wich we want to draw
		setVecOfCoords(_floors.getData(_StartCell)->getNaturalX(),_floors.getData(_StartCell)->getNaturalY());	 // chenging key STL
		//	trying to find ball wich we trying to drag
		map<vector<int> ,Ball>::iterator _moved = _BallMap.find(_coords);
		//	if success to find
		if((_moved) != _BallMap.end())
		{
			//	copy ballonly for draing
			Ball tempBall = (*_moved).second;
			//	change transperent
			(*_moved).second.setSelected();
			//	set coorinates on board
			tempBall.setX(_floors.getData(_EndCell)->getX());
			tempBall.setY(_floors.getData(_EndCell)->getY());
			//	draw him
			tempBall.Draw();
		}
	}

	//	Here we drawing ball on table on right 
	//	this is a new balls not located on bard game(cells)
	for(int i =0;i<(int)_newBalls.size();i++)
		_newBalls[i].Draw();					//	draw
	
	//	Here is section of print game points
	char PointsChar[10];						//	temp variable
	sprintf_s(PointsChar,"%d",GamePoints);		//	convert into string
	glutPrint(0.06f, 0.63f, PointsChar, 1.0f, 1.0f, 1.0f, 0.5f);	//	print

	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut
	
}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	// we call the display function
	//display();	

	static unsigned int lol;

	if(lol < 10)
	{
		LoadGame();
		lol = 10;
	}

	lol++;

	if(lol >= _PostRedisplay)
	{
		glutPostRedisplay();
		lol = 10;
	}
	
}

//=============================================================================
GameController::GameController()
{
	//	Glut load call set i.e.
	char *argv[] = {"Lines"};
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize (_WindowWidth,_WindowHeight); 
	glutInitWindowPosition (10,10);
	//glPointSize(POINT_SIZE/WINDOW_HEIGHT);
	glutCreateWindow ("Lines - By: Andrey Shamis AND Ilia Gaysinsky");
	glClearColor(1.0, 1.0, 1.0,1.0);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);							//	Glut//
	glLoadIdentity();										//	Glut
	//gluOrtho2D(0, _WindowWidth, 0, _WindowHeight);			//	Glut 
	//glOrtho(0, _WindowWidth, 0, _WindowHeight, -1.0,1.0);
	glutReshapeFunc(resizeWindow);	
	LoadCallBacksForGlut();			// load call back for graph	
	glutMainLoop();
}

//=============================================================================
// the function which load call back for glut 
void GameController::LoadCallBacksForGlut()
{
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);
	glutMotionFunc(mouseMove); 
	glutKeyboardFunc(KeyPress);
}

//=============================================================================
// the function which provide resize window
void GameController::resizeWindow(int w, int h)
{
	_WindowHeight = (h>1) ? h : 2;
	_WindowWidth =  (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);			//	INSIZE************************
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	//gluOrtho2D(0, _WindowWidth, 0, _WindowHeight);			//	Glut 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}