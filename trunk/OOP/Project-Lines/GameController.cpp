#include "GameController.h"
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
vector <Ball>			GameController::_postBalls;
vector <BallColor>		GameController::_AllColors;
FMOD::Sound*			GameController::_sounds[MAX_SOUNDS];
Graph<Floor>			GameController::_floors;
FMOD::System*			GameController::_system;
map<_MAP_KEY, Ball>	GameController::_BallMap;

_MAP_KEY				GameController::_coords;
vector<Ball>			GameController::_Balls;
bool					GameController::_BallEraseBoard[_BOARD_SIZE_X][_BOARD_SIZE_Y];
int						GameController::PrevFounded = 0;
int						GameController::GamePoints = 0;
bool					GameController::_bombExist = false;

int						GameController::GameStatus = _STATUS_GAME_OFF;
//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}
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
	if(key == _KEY_EXIT_GAME)
		exit(EXIT_SUCCESS);					//	for exit from game
	else if(key == _KEY_NEW_GAME)
		RealodGame();						//	for reload game
}

//=============================================================================
/*
 *		Function wich random create new balls and put them into temp vector
 *	and then they be taken from the temp vector
 */
void GameController::CreateBall()
{
	int					i	= 0;			//	temp variable
	const int newBallsSize	= rand()%_BALLS_MAX_SIZE_PER_PUTING+1;//number of new balls
	const float startX		= _POS_BALL_X_START;//	start coordinates
	float		startY		= _POS_BALL_Y_START;//	start coordinates

	//	Check if have to put ball
	while (i <=newBallsSize)
	{
		int startRand = 0;					//	temp parameters
		int stopRand = 7;					//	temp parameters
		bool giveSpecial = false;

		//	Here is few block of seting parameters for random
		if(rand()%6 == 2)					//	rand multicolor ball and bomb
			giveSpecial = true;				//	temp parameters

		if(rand()%7 < rand()%3)
		{									//	multi color section
			startRand = 7;					//	temp parameters
			stopRand = 10;					//	temp parameters
		}
		else if(giveSpecial && rand()%3 < rand()%2)
		{									//	mix and B color section
			startRand = 10;					//	temp parameters
			stopRand = 12;					//	temp parameters
		}

		//	Here is section for get random ball	
		const int newBallColor = rand()%(stopRand -startRand) + startRand;
		Ball tempBall = _Balls[newBallColor];//	create-copy ball
		tempBall.setCord(startX,startY);	//	set parameters of new ball
		tempBall.setPosition(-1,-1);		//	set parameters of new ball
		_newBalls.push_back(tempBall);		//	put to ProBalls DB
		i++;								//	increase counter
		startY+=_POS_BALL_Y_OFFSET;			//	increase new coordinate
	}
}
//=============================================================================
//	Function wich toke the balls crated before and put them ob board
void GameController::PutBall()
{
	const float offsetX = FLOOR_SIZE/_WindowWidth,	//	Picture corection
				offsetY = FLOOR_SIZE/_WindowHeight;	//	Picture corection
	int RandSize = 0;					//	temp variable
	vector<int> _freeFloors;

	Graph<Floor>::GraphIterator<Floor> it(_floors);	//	Get iterator of graph

	//	For each cell check if can put ball there
	for(;it != it.end() &&  _newBalls.size();it++)
		if(!(*it)->getBalled())
			_freeFloors.push_back((*it)->getID());
	
	//	While have balls on ProGame Vector of balls and can put balls
	while(_newBalls.size() && _BallCounter < (int)_floors.countNodes() &&_freeFloors.size())
	{
		int rnd_id = rand()%(_freeFloors.size());	//	get random free floor
		
		int xNat = _floors.getData(_freeFloors[rnd_id])->getNaturalX();
		int yNat = _floors.getData(_freeFloors[rnd_id])->getNaturalY();
		float xPos = _floors.getData(_freeFloors[rnd_id])->getX();
		float yPos = _floors.getData(_freeFloors[rnd_id])->getY();
		
		//	Coordiante setting
		_newBalls[0].setCord(xPos,yPos);		//	set grafiv position
		_newBalls[0].setPosition(xNat,yNat);	//	set position
		_newBalls[0].setID(_freeFloors[rnd_id]);//	set ball id like cell id
		_newBalls[0].mustBorn();
		setKey(xNat,yNat);						// STL Prepare put ball into map
		//	Put into map
		_BallMap.insert(pair<_MAP_KEY,Ball>(_coords,_newBalls[0]));
		//	erase ball from Progame vector
		_newBalls.erase(_newBalls.begin()) ;

		_floors.getData(_freeFloors[rnd_id])->setBalled(true);//update setings of cell
		_floors.tempDetach(_freeFloors[rnd_id],true);

		_BallCounter++;							//	increase ball counter
		_freeFloors.erase(_freeFloors.begin()+rnd_id);

	}

	if(_BallCounter == (int)_floors.countNodes())
	{
		cout << "Game OVER\n";
		GameStatus = _STATUS_GAME_END;
	}
	else
		playSound(Appear);	
}
void GameController::BumAroundBomb(const short int &_x,const short int &_y)
{
	short int xStart = _x-1;
	short int yStart = _y-1;
	short int xEnd = _x+1;
	short int yEnd = _y+1;
	if(xStart<0)
		xStart = _x;
	if(xEnd>=8)
		xEnd = _x;
	if(yStart<0)
		yStart = _y;
	if(yEnd>=8)
		yEnd = _y;
	map<_MAP_KEY,Ball>::iterator b1;
	for(int i = xStart; i<=xEnd;i++)
	{
		for(int j=yStart; j<=yEnd;j++)
		{
			setKey(i,j);
			b1 = _BallMap.find(_coords);
			if(b1 != _BallMap.end())
				_BallEraseBoard[i][j] = true;
		}

	}
}
//=============================================================================
//	Function wich do all postmoved operations
//	The function called to another function find by diogonale vericale
//	Puting temp data into bool variable wich provaide note for balls
//	wich need remove from table game
void GameController::BumBum()
{
	int counter_Balls = 0;					//	temp variable
	bool sound = false;

	//	Prepare the boolean data for new action
	memset(_BallEraseBoard,0,sizeof(_BallEraseBoard)*sizeof(bool));
	checkRowsAndCols();						//	check rows and cols
	checkDiagonals();						//	check diagonals

	if(_bombExist)
		for(int i = 0; i<_BOARD_SIZE_X;i++)
			for(int j=0; j<_BOARD_SIZE_Y;j++)
				if(_BallEraseBoard[i][j])		//	if bool seted
				{
					setKey(i,j);		//	set temp parameters of map
					if(_BallMap[_coords].doYouABall())
						BumAroundBomb(i,j);
				}

	//	For each cell on board game - each bool element seted
	for(int i = 0; i<_BOARD_SIZE_X;i++)
	{
		for(int j=0; j<_BOARD_SIZE_Y;j++)
		{
			if(_BallEraseBoard[i][j])		//	if bool seted
			{
				setKey(i,j);		//	set temp parameters of map
				_postBalls.push_back(_BallMap[_coords]);
				_postBalls[_postBalls.size()-1].mustDie();
				//	Cells oprations BFS fix- need
				_floors.tempDetach(_BallMap[_coords].getID(),false);//	put back ages
				_floors.getData(_BallMap[_coords].getID())->setBalled(false);
				_BallMap.erase(_coords);	//	erase ball
				counter_Balls++;			//	increase counter of fiunded balls
				sound = true;

				//playSound(Disappear);
			}
		}
	}
	if(sound)
	{
		playSound(Disappear);
		sound = false;
	}
	_bombExist = false;

	//	Game points manipulation
	if(counter_Balls>0)
		PrevFounded++;						//	if previous move you get balls
	else									//	if previuos maove you not success find
		PrevFounded = 0;

	GamePoints+=PrevFounded*counter_Balls*50;	//	update agame points
	_BallCounter -=counter_Balls;				//	update ball counter
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
	map<_MAP_KEY,Ball>::const_iterator it1,it2;

	while((start + matchCounter) < (9-i))
	{
		if(direc == Row)
		{
			setKey(i+start, start);
			it1 = _BallMap.find(_coords);
			setKey(i+start+matchCounter, start + matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else if(direc == Column)
		{
			setKey(start, i+start);
			it1 = _BallMap.find(_coords);
			setKey(start + matchCounter, i+start+matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else if (direc == BackRow)
		{
			setKey(((8-i)-start), start);
			it1 = _BallMap.find(_coords);
			setKey((((8-i)-start)-matchCounter), start + matchCounter);
			it2 = _BallMap.find(_coords);
			
		}
		else
		{
			setKey((8-start), i+start);
			it1 = _BallMap.find(_coords);
			setKey(((8-start)-matchCounter), i+start+matchCounter);
			it2 = _BallMap.find(_coords);
		}

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
		if(it1->second.doYouMulColor())
		{
			;
		}

		short int end = start + matchCounter;
		while(start != end)
		{
			if(direc == Row)
				_BallEraseBoard[i+start][start] = true;

			else if(direc == Column)
				_BallEraseBoard[start][i+start] = true;

			else if(direc == BackRow)
				_BallEraseBoard[((8-i)-start)][start] = true;
			else
				_BallEraseBoard[(8-start)][i+start] = true;


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
	map<_MAP_KEY,Ball>::const_iterator it1,it2;

	while((start + matchCounter) < 9)// && start < 6)
	{
		if(direc == Row)
		{
			setKey(i, start);
			it1 = _BallMap.find(_coords);
			setKey(i, start + matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else
		{
			setKey(start, i);
			it1 = _BallMap.find(_coords);
			setKey(start + matchCounter, i);
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
/*
bool GameController::ballsComp(map<_MAP_KEY,Ball>::const_iterator &b1,
							   map<_MAP_KEY,Ball>::const_iterator &b2)
{
	if (b1 == _BallMap.end() || b2 == _BallMap.end())
		return false;

	else if (b1->second == b2->second)
		return true;

	else
		return false;
}*/
//=============================================================================
//
bool GameController::ballsComp(map<_MAP_KEY,Ball>::const_iterator &b1,
							   map<_MAP_KEY,Ball>::const_iterator &b2)
{
	if (b1 == _BallMap.end() || b2 == _BallMap.end())
		return false;

	if (b1->second.doYouABall() || b2->second.doYouABall())
		_bombExist = true;

	return(b1->second == b2->second);

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
//	Function for loading Board Cells. This function work only once
//	And the next games use again the structure was loaded
void GameController::loadFloors()
{
	float startX = _POS_FLOOR_X_START;				//	Start coordinates
	float startY = _POS_FLOOR_Y_START;				//	Start coordinates
	unsigned int prev_vertex = 0;					//	Previous vertex ID
	const float offsetX = FLOOR_SIZE/_WindowWidth;	//	Grafic fix
	const float offsetY = FLOOR_SIZE/_WindowHeight;	//	Grafic fix
	vector <unsigned int> _prevLine;				//	Structure for build edges
	vector <unsigned int> _thisLine;				//	Structure for build edges
	Floor tempFloor;								//	Temp Variable

	//	Start load and locate floor cells
	for (int i=0;i<_BOARD_SIZE_X;i++)
	{
		prev_vertex = 0;							//	ID of last floor
		for (int j=0;j<_BOARD_SIZE_Y;j++)
		{
			Floor newFloor = tempFloor;				//	Copy floor
			newFloor.setCord(startX,startY);		//	Set parameters
			newFloor.setPosition(i,j);				//	Set parameters

			unsigned int newVert = _floors.addVertex(newFloor);	//	get ID
			_floors.getData(newVert)->setID(newVert);			//	Update ID

			_thisLine.push_back(newVert);			//	put in vector
			if(i>0)									//	if on second row
				_floors.addEdge(_prevLine[j],_thisLine[j]);
			if(prev_vertex)							//	if on second column
				_floors.addEdge(prev_vertex,newVert);
			
			prev_vertex = newVert;					//	update previous ID
			startY +=offsetY;						//	increase new position
		}
		startY =_POS_FLOOR_Y_START;					//	Reset position
		startX +=offsetX;							//	Update new position

		_prevLine.clear();							//	clear vector
		_prevLine = _thisLine;						//	copy vector
		_thisLine.clear();							//	clear vector
	
	}
}

//=============================================================================
//	Function is used in loading class
void GameController::LoadGame()
{
	srand(time((int)NULL));					//	Set rand for rundom operations

	GameStatus = _STATUS_GAME_ON;			//	set game status
	loadFloors();							//	load floors to memory
	loadSounds();							//	load sound
	loadBalls();

	playSound(BackGround);					//	start play background sound
	CreateBall();							//	create ball
	PutBall();								//	put ball
	CreateBall();							//	create ball
}

//=============================================================================
//	Function for convert all floors to simple not selected
void GameController::FloorDoAllSimple()
{
	//	Get graph iterator
	Graph<Floor>::GraphIterator<Floor> itSimple(_floors);
	for(;itSimple != itSimple.end() ;itSimple++)
		(*itSimple)->setFloorType(Simple);			//	set be simple
}

//=============================================================================
//	Function wich looking for floor wich we want start work
//	Function get parameters of mause
//	Function return ID of floor need us or -1 on fail
int GameController::FindFloorByCord(const float &xPos ,const float &yPos)
{
	float CELL_SIZE_X = FLOOR_SIZE/_WindowWidth;	//	Get height and with off cell
	float CELL_SIZE_Y = FLOOR_SIZE/_WindowHeight;	//	Get height and with off cell
	float _X , _Y;									//	temp variable

	Graph<Floor>::GraphIterator<Floor> it(_floors);	//	Graph iterator
	
	//	For each entry in graph
	for(;it != it.end() ;it++)
	{
		_X = (*it)->getX();							//	get X
		_Y = (*it)->getY();							//	get Y
		//	Check positions on game world
		if(_X <= xPos-CELL_SIZE_X  && (_X+CELL_SIZE_X ) > xPos-CELL_SIZE_X 
			&&  _Y <= yPos && _Y+CELL_SIZE_Y> yPos)
			return((*it)->getID());					//	return ID
	}
	return(-1);										//	return FAIL
}

//=============================================================================
//	Function for preparing to draw selected cells-floors
void GameController::PrepareSimplePath()
{
	
	//	Check if need run simple path
	if( _EndCell >0 && _StartCell > 0 && _StartCell != _EndCell)
	{
		int		_inVec		=	0,				//	temp variable
				vect_Size	=	0;				//	vector size


		//	before looking for simple path
		_floors.tempDetach(_StartCell,false);	//	Temporary return back edges
		//	of cell from wich we start do simple path
		//	Run simple path and get vector
		vector<int> _bfsVec = _floors.getVectorOfSimplePath(_StartCell,_EndCell);
		
		vect_Size	=	   (int)_bfsVec.size();	//	get vector size
		//	Start search in vector if founed is good
		for (int i=0;i<vect_Size;i++)
			if(_bfsVec[i] == _EndCell)			//	Compare last value
			{
				_inVec = _bfsVec[i];			//	Start draw from this node
				_canAddBalls = true;			//	Set true to options move ball
				break;							//	Break search
			}

		while(_inVec > 0)						//	If founded
		{
			//	Get futher of BFS algoritm select him
			_floors.getData(_inVec)->setFloorType(Selected);
			_inVec = _floors.getBfsDfsFather(_inVec);
		}

		_floors.tempDetach(_StartCell,true);	//	Return back edges		
	}
	
}
//=============================================================================
//	Function this is callback for mouse move
void GameController::mouseMove(int x,int y)
{
	if(_StartCell>0)
	{
		const float xPos = ((float)x)/((float)(WINDOW_WIDTH));		//	Mouse coord
		const float yPos =1.0f- ((float)y)/((float)(WINDOW_HEIGHT));//	Mouse coord
		int prev_end_value	= _EndCell;				//	for minimize search
		int f_val = FindFloorByCord(xPos,yPos);		//	get floor ID
		
		//	Check if floor ID finded and the floor not balled
		if(f_val>0 && !_floors.getData(f_val)->getBalled())
		{
			_EndCell = f_val;						//	Set parameters of end cell
			//_canAddBalls = true;					//	Flag for can move
		}
		else
		{
			_EndCell = 0;							//	Not founded set END 0
			_canAddBalls = false;					//	Flag dont move ball
		}
		
		if(_EndCell !=prev_end_value)				//	Check if path changed
		{
			FloorDoAllSimple();
			if(_EndCell > 0)						//	if have end cell
				PrepareSimplePath();				//	do simple path
		}

	}	//	End condition if _Start selected
}
//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
	{
	float xPos = ((float)x)/((float)(WINDOW_WIDTH));	//	Calculatin postion of mouse
	float yPos = ((float)y)/((float)(WINDOW_HEIGHT));	//	Calculatin postion of mouse
	yPos = 1.0f-yPos;									//	Calculatin postion of mouse

	if(state == 0)										//	Check if mouse was pressed
	{
		_PostRedisplay = _FAST_REDISPLAY;				//	Set new value for grafic

		int f_val = FindFloorByCord(xPos,yPos);			//	Get id of cell under mouse

		if(f_val>0 && _floors.getData(f_val)->getBalled())
			_StartCell = f_val;							//	Set start cell be this cell
		else
			_StartCell = 0;								//	No start cell

	}
	else if(state == 1)
	{
		FloorDoAllSimple();								//	Set all floor be simple
		//	Check if need lock for end cell and this cell is empty
		if(_canAddBalls && _StartCell != _EndCell && _EndCell >0 && _StartCell>0)
			MouseUp();									//	Mouse Up Event function
		else 
			playSound(error);							//	bad ID`s error

		_StartCell = 0;									//	Reset parameters
		_EndCell = 0;									//	Reset parameters
		_PostRedisplay = _EASY_REDISPLAY;				//	set grafic manipulation
	}
}

//=============================================================================
//	This function called when mouse up and _start cell end _end cell
//	have need values.	Function moving the ball wich need move
void GameController::MouseUp()
{
	//	Get iterator to map
	setKey(_floors.getData(_StartCell)->getNaturalX(),_floors.getData(_StartCell)->getNaturalY());	
	map<_MAP_KEY ,Ball>::iterator itb = _BallMap.find(_coords);
	//	For each entry in map check if him ID equale to start cell
	if(itb != _BallMap.end() && ((*itb).second).getID() == _StartCell)
	{
		//	If found start move the ball

		int xNat = _floors.getData(_EndCell)->getNaturalX();//	set postions
		int yNat = _floors.getData(_EndCell)->getNaturalY();//	set postions
		setKey(xNat,yNat);									//	chenging key STL
		_BallMap[_coords] = _BallMap[(*itb).first];			//	map manipulation
		//	seting coordinates postions and right ID of new cell
		_BallMap[_coords].setCord(_floors.getData(_EndCell)->getX(),_floors.getData(_EndCell)->getY());
		_BallMap[_coords].setPosition(xNat,yNat);			//	position
		_BallMap[_coords].setID(_EndCell);					//	ID

		//cout << _floors.getData(_EndCell)->getNaturalX() << " " << _floors.getData(_EndCell)->getNaturalY() << "\n";

		_floors.tempDetach(_StartCell,false);				//	Untuch source cell
		_floors.tempDetach(_EndCell,true);					//	Detuch destination cell
		_floors.getData(_EndCell)->setBalled(true);			//	Ball destination cell
		_floors.getData(_StartCell)->setBalled(false);		//	Unball soure cell
		_BallMap.erase(itb);								//	delete previous key
		//_BallMap.insert(pair<_MAP_KEY,Ball>(_coords,tempBall));
		BumBum();											//	Lock for combination
		if(PrevFounded == 0)
		{
		PutBall();											//	Put balls on bord
		BumBum();											//	Lock for combination
		CreateBall();										//	Create new balls
		}

	}
}

//=============================================================================
//	Function for set key wich be used in get/find value from map
//	The function get two ints - this is position of values key
//	in our map, and function updating the private gobal value
void GameController::setKey(const int &coordX, const int &coordY)
{
//	Here used vector for set key
#ifdef _MAP_KEY_IS_VECint
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
#endif

//	Here used Struct for set key
#ifdef _MAP_KEY_IS_STRUCT
	_coords.x = coordX;			//	set X
	_coords.y = coordY;			//	Set y
#endif
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
	map<_MAP_KEY ,Ball>::iterator itb = _BallMap.begin();
	for(;itb != _BallMap.end() ;itb++)
		((*itb).second).Draw();					//	draw

	//	Here we drawing ball on table on which gone 
	//	this is a new balls not located on bard game(cells)
	for(int i =0;i<(int)_postBalls.size();i++)
		_postBalls[i].Draw();					//	draw

	//	Here is block of code wich provide animation on drag and drop
	if(_StartCell > 0 && _EndCell > 0 && _StartCell != _EndCell && _canAddBalls)
	{
		//	Get ball wich we want to draw
		setKey(_floors.getData(_StartCell)->getNaturalX(),_floors.getData(_StartCell)->getNaturalY());	 // chenging key STL
		//	trying to find ball wich we trying to drag
		map<_MAP_KEY,Ball>::iterator _moved = _BallMap.find(_coords);
		//	if success to find
		if((_moved) != _BallMap.end())
		{
			//	copy ballonly for draing
			Ball tempBall = (*_moved).second;
			//	change transperent
			(*_moved).second.setSelected();
			//	set coorinates on board
			tempBall.setCord(_floors.getData(_EndCell)->getX(),_floors.getData(_EndCell)->getY());
			//tempBall.setY();
			//	draw him
			tempBall.Draw();
		}
	}

	//	Here we drawing ball on table on right 
	//	this is a new balls not located on bard game(cells)
	for(int i =0;i<(int)_newBalls.size();i++)
		_newBalls[i].Draw();					//	draw
	
	//	Here is section of print game points
	char PointsChar[_POINT_CHAR_SIZE];			//	temp variable
	sprintf_s(PointsChar,"%d",GamePoints);		//	convert into string
	glutPrint(0.06f, 0.63f, PointsChar, 1.0f, 1.0f, 1.0f, 0.5f);	//	print

	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut
	
}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	
	static unsigned int cGlutRedisplay;			//	For minimal use of grafik

	if(GameStatus == _STATUS_GAME_OFF)			//	Check if game loaded
		LoadGame();								//	Load game

	cGlutRedisplay++;							//	Grafic manipulation minize
	if(cGlutRedisplay >= _PostRedisplay)
	{
		glutPostRedisplay();					//	Call to redisplay
		cGlutRedisplay = 0;						//	reset counter
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
	glutIdleFunc(idle);					//	Call back for idle function
	glutDisplayFunc(display);			//	Call back for display function
	glutMouseFunc (mouseButton);		//	Call back for mouse click function
	glutMotionFunc(mouseMove);			//	Call back for mouse move function
	glutKeyboardFunc(KeyPress);			//	Call back for keyboard press function
}

//=============================================================================
// the function which provide resize window
void GameController::resizeWindow(int w, int h)
{
	//glPointSize(3);
	_WindowHeight = (h>1) ? h : 2;
	_WindowWidth =  (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);		
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	//gluOrtho2D(0, _WindowWidth, 0, _WindowHeight);			//	Glut 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
		_system->createSound("Sounds/disappear.mp3", NULL, NULL, &_sounds[0])||
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
		case Disappear:		_system->playSound(FMOD_CHANNEL_FREE, _sounds[0], 
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
//=============================================================================
//=============================================================================
//=============================================================================