#include "GameController.h"
//=============================================================================
// singleton
GameController *GameController::_instance = NULL;
// initialize static variables
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

_MAP_KEY			GameController::_coords;
vector<Ball>		GameController::_Balls;
bool			GameController::_BallEraseBoard[_BOARD_SIZE_X][_BOARD_SIZE_Y];
int					GameController::PrevFounded = 0;
int					GameController::GamePoints = 0;
bool				GameController::_bombExist = false;

int					GameController::GameStatus = _STATUS_GAME_OFF;
//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}
//=============================================================================
//	Function which prepare new game parameters such game points new balls
//	and other
void GameController::RealodGame()
{

	_BallMap.clear();				//	clear map
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
	CreateBall();					//	Create balls for next iteration
}
//=============================================================================
// Here is the function that print text at the window of the game
// get coordinates and color type
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
/*
 *		Function which random create new balls and put them into temp vector
 *	and then they be taken from the temp vector
 */
void GameController::CreateBall()
{
	int					i	= 0;			//	temp variable

	//number of new balls
	const int newBallsSize	= rand()%_BALLS_MAX_SIZE_PER_PUTING+1;
	const float startX		= _POS_BALL_X_START;//	start coordinates
	float		startY		= _POS_BALL_Y_START;//	start coordinates

	//	Check if have to put ball
	while (i <=newBallsSize)
	{
		int startRand = 0;					//	temp parameters
		int stopRand = 7;					//	temp parameters
		bool giveSpecial = false;

		//	Here is few block of setting parameters for random
		if(rand()%8 == 2)					//	rand multicolor ball and bomb
			giveSpecial = true;				//	temp parameters

		if(rand()%7 < rand()%3)
		{									//	multi color section
			startRand = 7;					//	temp parameters
			stopRand = 10;					//	temp parameters
		}
		else if(giveSpecial && rand()%8 < rand()%2)
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
//	Function which toke the balls crated before and put them ob board
void GameController::PutBall()
{
	const float offsetX = FLOOR_SIZE/_WindowWidth,	//	Picture correction
				offsetY = FLOOR_SIZE/_WindowHeight;	//	Picture correction
	int RandSize = 0;					//	temp variable
	vector<int> _freeFloors;

	Graph<Floor>::GraphIterator<Floor> it(_floors);	//	Get iterator of graph

	//	For each cell check if can put ball there
	for(;it != it.end() &&  _newBalls.size();it++)
		if(!(*it)->getBalled())
			_freeFloors.push_back((*it)->getID());
	
	//	While have balls on ProGame Vector of balls and can put balls
	while(_newBalls.size() && _BallCounter < (int)_floors.countNodes() 
														&&_freeFloors.size())
	{
		int rnd_id = rand()%(_freeFloors.size());	//	get random free floor
		
		int xNat = _floors.getData(_freeFloors[rnd_id])->getNaturalX();
		int yNat = _floors.getData(_freeFloors[rnd_id])->getNaturalY();
		float xPos = _floors.getData(_freeFloors[rnd_id])->getX();
		float yPos = _floors.getData(_freeFloors[rnd_id])->getY();
		
		//	Coordinate setting
		_newBalls[0].setCord(xPos,yPos);		//	set graphic position
		_newBalls[0].setPosition(xNat,yNat);	//	set position
		_newBalls[0].setID(_freeFloors[rnd_id]);//	set ball id like cell id
		_newBalls[0].mustBorn();
		setKey(xNat,yNat);						//STL Prepare put ball into map
		//	Put into map
		_BallMap.insert(pair<_MAP_KEY,Ball>(_coords,_newBalls[0]));
		//	erase ball from Progame vector
		_newBalls.erase(_newBalls.begin()) ;

		//update seatings of cell
		_floors.getData(_freeFloors[rnd_id])->setBalled(true);
		_floors.tempDetach(_freeFloors[rnd_id],true);

		_BallCounter++;							//	increase ball counter
		_freeFloors.erase(_freeFloors.begin()+rnd_id);

	}

	if(_BallCounter == (int)_floors.countNodes())
	{
		//cout << "Game OVER\n";
		Menu(_MNU_KEY_GAME_OVER);
		//GameStatus = _STATUS_GAME_END;
	}
	else
		playSound(Appear);	
}
//=============================================================================
//	Function which
void GameController::BumAroundBomb(const short int &_x,const short int &_y)
{
	short int xStart = _x-1;		//	boundary of X
	short int yStart = _y-1;		//	boundary of Y
	short int xEnd = _x+1;			//	boundary of X
	short int yEnd = _y+1;			//	boundary of Y

	if(xStart<0)
		xStart = _x;				//	set fixed boundary
	if(xEnd>=8)
		xEnd = _x;					//	set fixed boundary
	if(yStart<0)
		yStart = _y;				//	set fixed boundary
	if(yEnd>=8)
		yEnd = _y;					//	set fixed boundary

	map<_MAP_KEY,Ball>::iterator b1;	//	create iterator

	//	start search aariund bomb balls
	for(int i = xStart; i<=xEnd;i++)
	{
		for(int j=yStart; j<=yEnd;j++)
		{
			setKey(i,j);			//	prepare map
			b1 = _BallMap.find(_coords);	//	get vector

			if(b1 != _BallMap.end())	//	cgeck if exist
				_BallEraseBoard[i][j] = true;	//	update
		}
	}
}
//=============================================================================
//	Function which do all post moved operations
//	The function called to another function find by diagonals vertical
//	Putting temp data into bool variable which provide note for balls
//	which need remove from table game
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
					if(_BallMap[_coords].doYouABomb())
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
				//	Cells operations BFS fix- need, //	put back ages
				_floors.tempDetach(_BallMap[_coords].getID(),false);
				_floors.getData(_BallMap[_coords].getID())->setBalled(false);
				_BallMap.erase(_coords);	//	erase ball
				counter_Balls++;		//	increase counter of founded balls
				sound = true;
			}
		}
	}
	if(sound)
	{
		if(PrevFounded>0)
			playSound(double_bonus);	//	Play double sound
		else
			playSound(Disappear);		//	Play first set sound
		sound = false;
	}
	_bombExist = false;

	//	Game points manipulation
	if(counter_Balls>0)
		PrevFounded++;				//	if previous move you get balls
	else							//	if previous move you not success find
		PrevFounded = 0;

	GamePoints+=PrevFounded*counter_Balls*5;	//	update game points
	_BallCounter -=counter_Balls;				//	update ball counter
}

//=============================================================================
//	Function which check which diagonals balls series need to delete 
void GameController::checkDiagonals()
{
	for(short int i = _H_BOARD_SIZE; i >=0; i--)	// loop diagonals
	{
		scanDiagonal(i, Row);		// check left down diagonals
		scanDiagonal(i, Column);	// check left up diagonals
		scanDiagonal(i, BackRow);	// check right up diagonals
		scanDiagonal(i, BackColumn);// check right down diagonals
	}
}


//=============================================================================
//	Function which check which rows or columns balls series is need to delete
void GameController::checkRowsAndCols()
{
	for(short int i = 0; i < _BOARD_SIZE_X; i++)	// loop rows or columns
	{
		scanRowCol(i, Row);// check specific row
		scanRowCol(i, Column);//check specific col
	}
}

//=============================================================================
//	Function which update single diagonal series of balls that need to delete
//	it scan all the diagonals, walk on the map and camper balls.
//	get which diagonal to scan and which direction of X or Y scale.
void GameController::scanDiagonal(const short int &i, Direction direc)
{
	short int start = 0;				// define start point of series
	short int matchCounter = 1;			// define number of matched color balls
	map<_MAP_KEY,Ball>::const_iterator it1,it2; //define balls map iterators

	// Loop till reach last ball at series of 9 balls or less 
	while((start + matchCounter) < (_BOARD_SIZE-i))
	{
		// choose on which part and side need to scan upon direction - set the
		// iterators to right place, the first iter is start point and the
		// second iter is next balls, both of the may will change during the 
		// scan  
		if(direc == Row)		
		{
			setKey(i+start, start);				// set key for map of balls
			it1 = _BallMap.find(_coords);			
			setKey(i+start+matchCounter, start + matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else if(direc == Column)
		{
			setKey(start, i+start);				// set key for map of balls
			it1 = _BallMap.find(_coords);
			setKey(start + matchCounter, i+start+matchCounter);
			it2 = _BallMap.find(_coords);
		}
		else if (direc == BackRow)
		{
			setKey((((_BOARD_SIZE-1)-i)-start), start);// set key for map of
			it1 = _BallMap.find(_coords);
			setKey(((((_BOARD_SIZE-1)-i)-start)-matchCounter), 
										start + matchCounter);
			it2 = _BallMap.find(_coords);	
		}
		else
		{
			setKey(((_BOARD_SIZE-1)-start), i+start);//set key for map of balls
			it1 = _BallMap.find(_coords);
			setKey((((_BOARD_SIZE-1)-start)-matchCounter), 
									i+start+matchCounter);
			it2 = _BallMap.find(_coords);
		}
		if(ballsComp(it1,it2))		// camper cells (may be ball or floor)
		{
			matchCounter++;			// if equal -> incries match counter
		}
		else						
		{
			if (matchCounter >= _H_BOARD_SIZE+1) // mean that we already find right series
				break;

			start += matchCounter;	// start to scan from the new point
			matchCounter = 1;		// reset matches counter
		}
	}
	// this part responsible to update at bool 2D arr - where the series is 
	// located and it is update only if the series is 5 balls tenth
	if (matchCounter >= _H_BOARD_SIZE+1)			
	{
		short int end = start + matchCounter; // define end of series

		// loop till end of series choose on which part and side need to update
		// upon direction
		while(start != end)					  
		{
			if(direc == Row)
				_BallEraseBoard[i+start][start] = true;

			else if(direc == Column)
				_BallEraseBoard[start][i+start] = true;

			else if(direc == BackRow)
				_BallEraseBoard[(((_BOARD_SIZE-1)-i)-start)][start] = true;
			else
				_BallEraseBoard[((_BOARD_SIZE-1)-start)][i+start] = true;

			start++;				// promote counter 
		}
	}
}
//=============================================================================
//	Function which update single line series of balls that need to delete
//	it scan all the rows and columns, walk on the map and camper balls.
//	get: which rows or columns to scan and which direction of X or Y scale.
void GameController::scanRowCol(const short int &i, Direction direc)
{
	short int start = 0;				// define start point of series
	short int matchCounter = 1;			// define number of matched color balls
	map<_MAP_KEY,Ball>::const_iterator it1,it2;	// define balls map iterators 

	// Loop till reach last ball at series of 9 balls.
	while((start + matchCounter) < _BOARD_SIZE)
	{
		// choose on which part and side need to scan upon direction - set the
		// iterators to right place, the first iter is start point and the
		// second iter is next balls, both of the may will change during the 
		// scan 
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
		if(ballsComp(it1,it2))	// camper cells (may be ball or floor)
		{
			matchCounter++;		// if equal -> incries match counter
		}
		else
		{
			if (matchCounter >= _H_BOARD_SIZE+1)	// mean that we already find right series
				break;

			start += matchCounter;	// start to scan from the new point
			matchCounter = 1;		// reset matches counter
		}
	}
	// this part responsible to update at bool 2D arr - where the series is 
	// located and it is update only if the series is 5 balls tenth
	bool canSet = false;
	if (matchCounter >= _H_BOARD_SIZE+1)			
	{
		short int end = start + matchCounter; // define end of series

		if(direc == Row && CheckColsRowsFix(start,end,i,Row))
			canSet = true;
		else if(direc == Column &&CheckColsRowsFix(start,end,i,Column))
			canSet = true;
		else
			canSet = false;
		
		

		// loop till end of series choose on which part and side need to update
		// upon direction
		while(start != end && canSet)					  
		{
			if(direc == Row)
				_BallEraseBoard[i][start] = true;
			else 
				_BallEraseBoard[start][i] = true;

			start++;				// promote counter 
		}
	}
}

//=============================================================================
//	Function for improving finding set wich can be
bool GameController::CheckColsRowsFix(const int start,const int end, const int rowCol,Direction direc)
{
	map<_MAP_KEY,Ball>::const_iterator it1,it2;	// define balls map iterators 
	//	For each balls check each ball with each ball
	for(int i= start+1 ;i<end;i++)
	{
		for(int j=i;j<end;j++)
		{
			if(direc == Row)
			{	//	check buy cols
				setKey(rowCol, i);
				it1 = _BallMap.find(_coords);
				setKey(rowCol, j);
				it2 = _BallMap.find(_coords);
			}
			else
			{	//	check buy rows
				setKey(i, rowCol);
				it1 = _BallMap.find(_coords);
				setKey(j,rowCol);
				it2 = _BallMap.find(_coords);
			}
			//	If not compared return false
			if(!ballsComp(it1,it2))
				return(false);
		}
	}

	return(true);			//	return true if this okey
}
//=============================================================================
//	Function which get to iterators of map of balls and beside if there two 
//	balls with the same color.
//  return true only if both of iterators point on balls (not end of map) and
//	thus balls are equal by their colors. otherwise return false.
bool GameController::ballsComp(map<_MAP_KEY,Ball>::const_iterator &b1,
							   map<_MAP_KEY,Ball>::const_iterator &b2)
{
	// Check if both of iterators point on balls (not end of map)
	if (b1 == _BallMap.end() || b2 == _BallMap.end())
		return false;

	// Check if both of iterators point on balls (not floors)
	if (b1->second.doYouABomb() || b2->second.doYouABomb())
		_bombExist = true;

	return(b1->second == b2->second); // call operator of comperation
}
//=============================================================================
//	Function that load balls objects
void GameController::loadBalls()
{
	float x=0,y=0;
	int nutX=-1,nutY=-1;

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
	srand(time((int)NULL));					//	Set rand for random operations

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
//	Function get parameters of mouse
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
		//	of cell from witch we start do simple path
		//	Run simple path and get vector
		vector<int> _bfsVec = _floors.getVectorOfSimplePath(_StartCell,_EndCell);
		
		vect_Size	=	   (int)_bfsVec.size();	//	get vector size
		//	Start search in vector if founded is good
		for (int i=0;i<vect_Size;i++)
			if(_bfsVec[i] == _EndCell)			//	Compare last value
			{
				_inVec = _bfsVec[i];			//	Start draw from this node
				_canAddBalls = true;			//	Set true to options move ball
				break;							//	Break search
			}

		while(_inVec > 0)						//	If founded
		{
			//	Get further of BFS algorithm select him
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
		const float xPos = ((float)x)/((float)(WINDOW_WIDTH));	//Mouse coords
		const float yPos =1.0f- ((float)y)/((float)(WINDOW_HEIGHT));
		int prev_end_value	= _EndCell;				//	for minimize search
		int f_val = FindFloorByCord(xPos,yPos);		//	get floor ID
		
		//	Check if floor ID friended and the floor not balled
		if(f_val>0 && !_floors.getData(f_val)->getBalled())
		{
			_EndCell = f_val;					//	Set parameters of end cell
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
			_canAddBalls = false;					//	Flag dont move ball
			if(_EndCell > 0)						//	if have end cell
				PrepareSimplePath();				//	do simple path
		}

	}	//	End condition if _Start selected
}
//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
{
	//	Calculation position of mouse
	float xPos = ((float)x)/((float)(WINDOW_WIDTH));	
	float yPos = ((float)y)/((float)(WINDOW_HEIGHT));	
	yPos = 1.0f-yPos;	

	if(button == 0)
	{
		if(xPos >= 0.065 && xPos <= 0.175 && yPos >= 0.51 && yPos <= 0.56)
			Menu(_MNU_KEY_NEW_GAME);					//	Create new game
		else if(xPos >= 0.149 && xPos <= 0.188 && yPos >= 0.051 && yPos <= 0.104)
			Menu(_MNU_KEY_HELP);						//	shw help
		else
		{
			if(state == 0 && GameStatus == _STATUS_GAME_ON)	//	Check if mouse was pressed
			{

				_PostRedisplay = _FAST_REDISPLAY;		//	Set new value for graphic

				int f_val = FindFloorByCord(xPos,yPos); //	Get id of cell under mouse

				if(f_val>0 && _floors.getData(f_val)->getBalled())
					_StartCell = f_val;					//	Set start cell be this cell
				else
					_StartCell = 0;						//	No start cell
			}
			else if(state == 1 && GameStatus == _STATUS_GAME_ON)
			{
				FloorDoAllSimple();						//	Set all floor be simple
				//	Check if need lock for end cell and this cell is empty
				if(_canAddBalls && _StartCell != _EndCell && _EndCell >0 && 
																	_StartCell>0)
					MouseUp();							//	Mouse Up Event function
				else 
					playSound(error);					//	bad ID`s error

				_StartCell = 0;							//	Reset parameters
				_EndCell = 0;							//	Reset parameters
				_PostRedisplay = _EASY_REDISPLAY;		//	set graphic manipulation
			}
		}
	}
	if( state == 0 && GameStatus == _STATUS_GAME_SHOW_HELP)
	{
		Menu(_MNU_KEY_HELP_EXIT);
	}
}

//=============================================================================
//	This function called when mouse up and _start cell end _end cell
//	have need values.	Function moving the ball which need move
void GameController::MouseUp()
{
	//	Get iterator to map
	setKey(_floors.getData(_StartCell)->getNaturalX(),
		   _floors.getData(_StartCell)->getNaturalY());	
	map<_MAP_KEY ,Ball>::iterator itb = _BallMap.find(_coords);
	//	For each entry in map check if him ID equal to start cell
	if(itb != _BallMap.end() && ((*itb).second).getID() == _StartCell)
	{
		//	If found start move the ball

		int xNat = _floors.getData(_EndCell)->getNaturalX();//	set positions
		int yNat = _floors.getData(_EndCell)->getNaturalY();//	set positions
		setKey(xNat,yNat);									// changing key STL
		_BallMap[_coords] = _BallMap[(*itb).first];			// map manipulation

		//	setting coordinates positions and right ID of new cell
		_BallMap[_coords].setCord(_floors.getData(_EndCell)->getX(),
								  _floors.getData(_EndCell)->getY());
		_BallMap[_coords].setPosition(xNat,yNat);			//	position
		_BallMap[_coords].setID(_EndCell);					//	ID

		_floors.tempDetach(_StartCell,false);			//	Untuch source cell
		_floors.tempDetach(_EndCell,true);			//	Detuch destination cell
		_floors.getData(_EndCell)->setBalled(true);	//	Ball destination cell
		_floors.getData(_StartCell)->setBalled(false);	//	Unball soure cell
		_BallMap.erase(itb);							//	delete previous key
		//_BallMap.insert(pair<_MAP_KEY,Ball>(_coords,tempBall));
		BumBum();									//	Lock for combination
		if(PrevFounded == 0)
		{
			PutBall();									//	Put balls on board
			BumBum();									//	Lock for combination
			CreateBall();								//	Create new balls
		}

	}
}

//=============================================================================
//	Function for set key which be used in get/find value from map
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
//	Function call back which used in glut
//	From this function you can exit from the game
//	And Also you can Reload Game= Get new Game board
void GameController::KeyPress(unsigned char key, int x, int y)
{
	if(key == _KEY_EXIT_GAME)
		Menu(_MNU_KEY_EXIT_GAME);
	else if(key == _KEY_NEW_GAME)
		Menu(_MNU_KEY_NEW_GAME);		//	for reload game
	else if(key == _KEY_HELP)
		Menu(_MNU_KEY_HELP);			//	show help
	else if(key == _KEY_HELP_EXIT)
		Menu(_MNU_KEY_HELP_EXIT);		//	close help
}

//=============================================================================
//	Game menu
void GameController::Menu(const int val)
{
	if(val == _MNU_KEY_EXIT_GAME)
		exit(EXIT_SUCCESS);					//	for exit from game
	else if(val == _MNU_KEY_NEW_GAME)
	{
		GameStatus = _STATUS_GAME_ON;
		gameBoard.setShowMode(0);			//	close help
		RealodGame();						//	for reload game
	}
	else if(val == _MNU_KEY_HELP)
	{
		gameBoard.setShowMode(1);			//	show help
		GameStatus = _STATUS_GAME_SHOW_HELP;
	}
	else if(val == _MNU_KEY_HELP_EXIT)
	{
		gameBoard.setShowMode(0);			//	close help
		GameStatus = _STATUS_GAME_ON;
	}
	else if(val == _MNU_KEY_GAME_OVER)
	{
		gameBoard.setShowMode(2);			//	TODO DELETE
		GameStatus = _STATUS_GAME_END;		//	TODO DELETE
	}

}

//=============================================================================
// the function which create menu for glut
void GameController::CreateMenuForGlut()
{
	// main menu
	int menu = glutCreateMenu (Menu);
	glutAddMenuEntry ("New Game\tn",			_MNU_KEY_NEW_GAME);
	glutAddMenuEntry ("Show help\tg",			_MNU_KEY_HELP);
	glutAddMenuEntry ("Exit\tq",				_MNU_KEY_EXIT_GAME);
	glutAttachMenu (GLUT_RIGHT_BUTTON);
}
//=============================================================================
//	Display function
void GameController::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	gameBoard.Draw();							//	Draw background board

	if(GameStatus != _STATUS_GAME_SHOW_HELP && GameStatus != _STATUS_GAME_END)
	{
		//	Here we drawing the cells of board
		Graph<Floor>::GraphIterator<Floor> it(_floors);
		for(;it != it.end() ;it++)
			(*it)->Draw();							//	draw

		//	Start work with map of balls and draw balls located on board
		map<_MAP_KEY ,Ball>::iterator itb = _BallMap.begin();
		for(;itb != _BallMap.end() ;itb++)
			((*itb).second).Draw();					//	draw

		//	Here we drawing ball on table on which gone 
		//	this is a new balls not located on bard game(cells)
		for(int i =0;i<(int)_postBalls.size();i++)
			_postBalls[i].Draw();					//	draw

		//	Here is block of code which provide animation on drag and drop
		if(_StartCell > 0 && _EndCell >0 && _StartCell != _EndCell && _canAddBalls)
		{
			//	Get ball which we want to draw
			setKey(_floors.getData(_StartCell)->getNaturalX(),  // changing key STL
				   _floors.getData(_StartCell)->getNaturalY());	 
			//	trying to find ball which we trying to drag
			map<_MAP_KEY,Ball>::iterator _moved = _BallMap.find(_coords);
			//	if success to find
			if((_moved) != _BallMap.end())
			{
				//	copy ballonly for drawing
				Ball tempBall = (*_moved).second;
				//	change transparent
				(*_moved).second.setSelected();
				//	set coordinates on board
				tempBall.setCord(_floors.getData(_EndCell)->getX(),
								 _floors.getData(_EndCell)->getY());
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

		GarbageColector();
	}
	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut
	
}
//=============================================================================
//	Garbage Collector function 
void GameController::GarbageColector()
{
	//	Check if size of vector so big for erase not used objects
	if(_postBalls.size() > _MAX_POST_REDISPLAY_VEC_SIZE)
	{
		//	check bounds for erase
		for(int i =0;_postBalls.size() > _MIN_POST_REDISPLAY_VEC_SIZE ;i++)
		{
			_postBalls.erase( _postBalls.begin()+i);	//	erase
			i--;										//	increase
		}
	}
}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	
	static unsigned int cGlutRedisplay;			//	For minimal use of graphic

	if(GameStatus == _STATUS_GAME_OFF)			//	Check if game loaded
		LoadGame();								//	Load game

	cGlutRedisplay++;							//	Graphic manipulation minize
	if(cGlutRedisplay >= _PostRedisplay)
	{
		glutPostRedisplay();					//	Call to redisplay
		cGlutRedisplay = 0;						//	reset counter
	}	
}

//=============================================================================
//
GameController::GameController()
{
	//	Glut load call set i.e.
	char *argv[] = {"Lines"};
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA );//GLUT_DEPTH
	glutInitWindowSize (_WindowWidth,_WindowHeight); 
	glutInitWindowPosition (10,10);
	//glPointSize(POINT_SIZE/WINDOW_HEIGHT);
	glutCreateWindow ("Lines - By: Mr. Andrey Shamis AND Mr. Ilia Gaysinsky");
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
	glutKeyboardFunc(KeyPress);			//Call back for keyboard press function
	CreateMenuForGlut();
}

//=============================================================================
// the function which provide resize window
void GameController::resizeWindow(int w, int h)
{
	//glPointSize(2);
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
//	Function that load sound files.
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
		_system->createSound("Sounds/double_bonus.mp3", NULL, NULL,
																&_sounds[2])||
		_system->createSound("Sounds/cautious-path.mp3", FMOD_LOOP_NORMAL, NULL,
																&_sounds[5]))
		// if sound doesn't loaded -> print erorr message and exit program
		printErrorMSG("createSound");		
} 

//=============================================================================
//	Function that print Error messages and exit program 
void GameController::printErrorMSG(char *sentence)
{
	cout << "Function: " << sentence << "fail\n";
	exit(EXIT_FAILURE);
}

//=============================================================================
//	Function is used to play specific sound.
void GameController::playSound(SoundsName soundName)
{
	// Create sound channel
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
		case BackGround:		_system->playSound(FMOD_CHANNEL_FREE,
												_sounds[5], false, &channel); 
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