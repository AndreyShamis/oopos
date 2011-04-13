#include "GameController.h"
//=============================================================================
// single tone
GameController *GameController::_instance = NULL;

//=============================================================================
// initiat static virb


graphKind	GameController::_grKind = Quad;
int			GameController::_grSize = 9;
int			GameController::_level = 0;
int			GameController::_pointSize = 20;
time_t GameController::time_game = 0;
time_t GameController::seconds = 0;
short int	GameController::_neighborSize = 0;
int	GameController::_WindowHeight;
int	GameController::_WindowWidth;
int	GameController::_ID_OF_CENTER_VERTEX = 0;
Graph<Vertex>  GameController::_someGraph;
Graph<Vertex>  GameController::_FullGraph;
Graph<Vertex>  GameController::_Solution;
char		GameController::timer[TIMER_SIZE];
bool GameController::_show_sol = false;
bool GameController::_update_timer = true;

//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}

//=============================================================================
// the function which create menu for glut
void GameController::CreateMenuForGlut()
{
	// sub menu
	int typeGraph = glutCreateMenu (Menu);
	glutAddMenuEntry ("Quad Graph\tq",			_QUAD);
	glutAddMenuEntry ("Hexagonal Graph\th",		_HEXG);	

	// main menu
	int menu = glutCreateMenu (Menu);
	glutAddSubMenu ("Type of Graph",				typeGraph);
	glutAddMenuEntry ("New Game\tn",				_NEW_GAME);
	glutAddMenuEntry ("Level Up\tl",				_LEVEL);
	glutAddMenuEntry ("Show solution\tl",			_SOLUTION);
	glutAddMenuEntry ("Exit\tx",					_EXIT);
	glutAttachMenu (GLUT_RIGHT_BUTTON);
}
//=============================================================================
//	Game menu
void GameController::Menu(int val)
{
	if(val == _EXIT){
		exit(EXIT_SUCCESS);		// exit game
	}
	else if(val == _NEW_GAME){
		ClearAll();
		createGameGraph();		// create game graph
	}
	else if(val == _LEVEL){
		_level++;				// go to the next level and creat the new graph
		ClearAll();
		createGameGraph();	
	}
	else if(val == _SOLUTION){
		_show_sol = true;		// show solution
		_update_timer = false;
	}
	else if(val == _QUAD){
		if(_grKind != Quad)
			_level =0;
		_grKind = Quad;			// swich to quad graph game type and				
		ClearAll();
		createGameGraph();		// creat the new graph
	}
	else if(val == _HEXG){
		if(_grKind != Hexagonal)
			_level =0;
		_grKind = Hexagonal;	// swich to Hexagonal graph game type and
		ClearAll();
		createGameGraph();		// creat the new graph
	}
}
//=============================================================================
void GameController::KeyPress(unsigned char key, int x, int y)
{

	if(key == _EXIT_CH){			// exit game
		Menu(_EXIT);
	}
	else if(key == _NEW_GAME_CH){	// create game graph
		Menu(_NEW_GAME);
	}
	else if(key == _LEVEL_CH){	// go to the next level and creat the new graph
		Menu(_LEVEL);
	}
	else if(key ==_SOLUTION_CH){	// show solution
		Menu(_SOLUTION);
	}
	else if(key == _QUAD_CH){		// swich to quad graph game type and	
		Menu(_QUAD);
	}
	else if(key == _HEX_CH){		// swich to Hexagonal graph game type and
		Menu(_HEXG);
	}

}
//=============================================================================
GameController::GameController()
{
	srand ( time(NULL) );
	glMatrixMode(GL_PROJECTION);		//	Glut
    glLoadIdentity();					//	Glut
    gluOrtho2D(0, 500, 0, 500);			//	Glut 
	_grKind = Hexagonal;				
}
//=============================================================================
void GameController::LoadGame()
{
	glutReshapeFunc(resizeWindow);	
	LoadCallBacksForGlut();			// load call back for graph
	createGameGraph();				// create game graph
}

//=============================================================================
// function create graph of the game
void GameController::createGameGraph()
{
	_show_sol = false;					//	set don`t show solution graph
	createFullGraph();					//	create graph
	_Solution = _someGraph;				//	set solution graph
	GraphGrinder();						//	set randomly potential edges
	FindElectrecisty();					//	find all good potential edges
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
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text); 
		text++; 
	} 
	if(!blending) glDisable(GL_BLEND); 
} 

//=============================================================================
//	This function over on all vertex in graph and do randomly
//	Shift for potential edges in vector
void GameController::GraphGrinder()
{	
	const int MAX_RAND_VALUE = 4;	//	max value of shifts

	//	Get iterator to all vertex in graph
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	//	For each vertex in graph
	for(;it != it.end() ;it++)
	{
		//	Get random number of shifts
		const int rnd = rand()%MAX_RAND_VALUE;
		//	call to function shift
		for(int i=0;i<rnd;i++){
			(*it)->Shift();
		}	
	}

}

//=============================================================================
// function creat fuul quad graph (K_rowSize.rowSize)
// get row size, recive nothing
void GameController::creatQuadGraph(const int rowSize)
{
	
	int id			= 0;		// id of veryex
	float x			= 0;		// coordinats of 
	float y			= 0;		// vertex
	int prev_id		= 0;		// id of privius vertex
    int col_size = rowSize;		// graph dimention

	_pointSize = 20 - _level*2;	// point size propoution

    for(int i= 0; i < rowSize;i++)		// loop x coordinate of vetexes
    {
        prev_id=0;						// reset previus id of vertex
        for(int j= 0; j< col_size;j++)	// loop y coordinate of vetexes
        {
            x = (float)(i+1)*(0.85)/rowSize;		// set x coordinate of vert
            y = (float)(j+1)*(0.85)/col_size;		// set y coordinate of vert
            Vertex newVertex(x,y,4,1.0/rowSize);
            id =_someGraph.addVertex(newVertex);	// add vertex to graph
			_someGraph.getData(id)->SetID(id);		// set id of vertex

            if(prev_id)
				_someGraph.addEdge(prev_id,id);

			// part of building full graph (add the right edges)
            if(i)
				_someGraph.addEdge(id-rowSize,id);

            prev_id=id;
            
			// set the centeral vertex id
			if((rowSize-1)/2 == i && (col_size-1)/2 == j) 
				_ID_OF_CENTER_VERTEX = id;
        }

    }   
}
//=============================================================================
// function creat fuul quad graph (K_size.size)
// get side size, recive nothing
void GameController::creatHexagonalGraph(const int size)
{
	_ID_OF_CENTER_VERTEX = 0;			// reset id of centerul vertex
	vector<int> _layer;					// vector of curent layer of vertexes
	vector<int> _layer_new;				// vector of new layer of vertexes
	int start = 2  ;					// define start point to loop
	float dist	= (1-0.23)/(2*size);	// define distance between vertexes
	int counter = 0;			// counter for definition of centeral vertex id

	// culculation of definig of centeral vertex
	for(int i= size/2 +1; i < size; i++) 
		_ID_OF_CENTER_VERTEX += i;
	_ID_OF_CENTER_VERTEX += (size/2 +1);

	_pointSize = 20 - _level*2;	// point size propoution					

	for(int i =0;i<size;i++)	// loop x coordinate of vetexes
	{
		int id_prev = 0;		// reset previus id of vertex
		// loop y coordinate of vetexes
		for(int j=start;j<2*size-((_level)*2)-start;j+=2)
		{
			// set x and y coordinate of vert
			float x = (float)(_level+1)*dist + float(j+1)*dist;	
			float y = (float)(_level+1)*dist+ 1.8*((i+1-(float)(i*0.05)))*dist;

			Vertex newVertex(x,y,6,dist*2.1);				// create vertex
			int id = _someGraph.addVertex(newVertex);	// add vertex to graph
			_someGraph.getData(id)->SetID(id);			// set id of vertex

			// set curent layer of vertexes (for building full graph)
			_layer_new.push_back(id);					

			// set the centeral vertex id
			counter++;
			if(_ID_OF_CENTER_VERTEX == counter)
				_ID_OF_CENTER_VERTEX = id;

			// part of building full graph (add the right edges)
			if(id_prev)
			{
				_someGraph.addEdge(id,id_prev);
			}
			id_prev = id;
		}
		// navigate graph building direction ( choose edges to builde ) 
		
		//	Adding edges in depends of line position to center line
		if(i<(size+1)/2)			{
			//	Above center line and on center line
			const int vec_size  = _layer.size();
			for(int is=0;is<vec_size;is++){
				//	Add two edges
				_someGraph.addEdge(_layer[is],_layer_new[is]);
				_someGraph.addEdge(_layer[is],_layer_new[is+1]);
			}
		}
		else{
			//	Under center line
			const int vec_size  = _layer_new.size();
			for(int is=0;is<vec_size;is++){	
				//	Add two edges
				_someGraph.addEdge(_layer_new[is],_layer[is+1]);
				_someGraph.addEdge(_layer_new[is],_layer[is]);
				
			}		
		}
		// navigate graph building direction
		if(i<(size)/2)
			start--;
		else
			start++;	

		// switch lyers
		_layer = _layer_new;
		_layer_new.clear();
	}
}

//=============================================================================
// function that
void GameController::createFullGraph()
{
	_update_timer = true;
	time_game = time(NULL);	
	// define neihbors size
	if(_grKind == Quad)
	{
		_neighborSize = 4;
		creatQuadGraph(5+_level*2);
	}
	else
	{
		_neighborSize = 6;
		creatHexagonalGraph(5+_level*2);
	}
	_FullGraph = _someGraph;	// copy full graph

	///	Looking for rundom DFS vertex
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	int StartVertex =  rand()%(_someGraph.countNodes()-1);
	int i=0;
	for(;it != it.end() ;it++)
	{
		if(StartVertex == i){
			StartVertex = (*it)->GetID();
			break;
		}
		i++;
	}

	// Get vector of ids by DFS
	vector<int> DFS = _someGraph.getVectorOfIdsDFS(StartVertex);

	vector<AddEdges> _back_adg;
	const int vecSize0 =	  (int)DFS.size();

	// creation of potential edges. firs we put them to temp vector of edges, 
	// each edge contain id of tow vertex in graph
	for(i=0;i<vecSize0;i++)
	{
		Graph<Vertex>::NeighborIterator<Vertex> nei(_someGraph,DFS[i]);
		for(;nei != nei.end() ;nei++)
		{
			bool found = false;
			for(int j = i-1;j>=0;j--)
			{
				if(DFS[j] == (*nei)->GetID())
				{
					AddEdges tmp;
					tmp.vert1 = DFS[i];
					tmp.vert2 = DFS[j];
					_back_adg.push_back(tmp);
					found = true;
					break;
				}
			}

			if(found){
				break;
			}
		}		
	}

	// all vertexes detached from thire edges, befor of reconstruction
	// of spaning tree that was geted from DFS alg' 
	const int vecSize = (int)DFS.size();
	for(int i=0;i<vecSize;i++)
	{
		_someGraph.detachVertex(DFS[i]);
	}

	// reconstruction of spaning tree that was geted from DFS alg' 
	const int vecSize2 =(int)_back_adg.size(); 
	for(int i=0;i<vecSize2;i++)
	{
	// Alignment of values ​in the vector potential neighbors depending 
	//	on the angle between the two

		const float vert1X	= _someGraph.getData(_back_adg[i].vert1)->getX() ;
		const float vert1Y  = _someGraph.getData(_back_adg[i].vert1)->getY();
		const float vert2X  = _someGraph.getData(_back_adg[i].vert2)->getX();
		const float vert2Y	 =_someGraph.getData(_back_adg[i].vert2)->getY();

		if(_grKind == Quad)
		{
		// we chek for all engels position in graph between two vertexes in 
		// depen of thier angels
			if(vert1X>vert2X){   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(0);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(2);
			}
			else if(vert1X<vert2X){
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(2);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(0);
			}
			else if(vert1Y>vert2Y){   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(1);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(3);
			}
			else if(vert1Y<vert2Y){
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(3);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(1);
			}
		}
		else if(_grKind == Hexagonal)
		{
		// we chek for all engels position in graph between two vertexes in 
		// depen of thier angels
			if(vert1X > vert2X && vert1Y > vert2Y){   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(1);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(4);
			}
			else if(vert1X < vert2X && vert1Y < vert2Y){  
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(4);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(1);
			}
			else  if(vert1X > vert2X && vert1Y == vert2Y){
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(0);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(3);

			}
			else  if(vert1X < vert2X && vert1Y == vert2Y){
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(3);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(0);
			}
			else if(vert1X > vert2X && vert1Y < vert2Y){   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(5);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(2);
			}
			else if(vert1X < vert2X && vert1Y > vert2Y){  
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(2);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(5);
			}			
		}
	}
}
//=============================================================================
// function that clear all data at the graph
void GameController::ClearAll()
{
	// use of graph iterator clearing all vertexes
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	for(;it != it.end() ;it++)
	{
		_someGraph.removeVertex((*it)->GetID());
	}
	_FullGraph = _someGraph;		// reset full graph 
	_Solution = _someGraph;			// reset solution graph 

}



//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
{

	// create BFS vector of graph through sorce vertex as senteral vertex
	const vector<int> _vec =  _someGraph.getVectorOfIdsBFS(_ID_OF_CENTER_VERTEX);

	// chek if the game is solved (all light is lights) - go to the next level
	if(_vec.size() == _someGraph.countNodes())
	{
		_level++;
		ClearAll();
		createGameGraph();
	}
	// roll the potetial edges
	if(button == 0 && state == 1 && !_show_sol)
	{
		float xPos = ((float)x)/((float)(_WindowWidth-1));
		float yPos = ((float)y)/((float)(_WindowHeight-1));
		yPos = 1.0f-yPos;
		
//		Graph<Vertex>::GraphIterator<Vertex> detach(_someGraph);
		//	Detach all edges in graph
//		for(;detach != detach.end();detach++)
//		{
//			_someGraph.detachVertex((*detach)->GetID());
//		}
							
		//	Looking For Pressed Vertex
		Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
		float resx = 1000;		//	Default value
		float resy = 1000;		//	Default value
		int id = 0;				//	vertex nea to klick place
		for(;it != it.end() ;it++)
		{
			float vertX = (*it)->getX();	//	get coordinate
			float vertY = (*it)->getY();	//	also

			//	Try find minimap disrtance
			if(abs(vertX-xPos) <=  resx && abs(vertY-yPos) <= resy)
			{
				//	If found minimal  update flags and counters values
				resx = abs(vertX-xPos);
				resy = abs(vertY-yPos);
				id = (*it)->GetID();		//	set new id
			}
		}
		//	End pressed Vertex
		_someGraph.detachVertex(id);
		_someGraph.getData(id)->Shift();	//	Shift the vertex
		FindElectrecisty();		
	}


}

//=============================================================================
// get source  vertex id   and place in maybe edge vertex
// get source vertex id and potential vertex derection position
void GameController::ElectricityQuadr(const int srcID,const int plc)
{
	// get vertex position 
	const float srcX = _someGraph.getData(srcID)->getX();
	const float srcY = _someGraph.getData(srcID)->getY();
	
	// get all posible nieghbors from full graph
	Graph<Vertex>::NeighborIterator<Vertex> it2(_FullGraph,srcID);
	
	// for all neighbors - comper between potential edges, depend on angle
	for(;it2 != it2.end();it2++)
	{
		const int neiID =   (*it2)->GetID();
		const vector<bool> _futedgesS = _someGraph.getData(neiID)->getFutEdg();

		// if some posible angle in posibel edge exist.
		if(_futedgesS[(plc+(_neighborSize/2))%_neighborSize])
		{
			const float neX = _someGraph.getData(neiID)->getX();
			const float neY = _someGraph.getData(neiID)->getY();
		
			const float sumX = neX - srcX;
			const float sumY = neY - srcY;

			// calculation of angle
			if(plc%2 == 0 && sumX)
			{	
				if(sumX < 0 && (plc+_neighborSize/2) < _neighborSize  )
				{
					_someGraph.addEdge(srcID,neiID);					
				}
				else if(sumX > 0 && (plc+_neighborSize/2) >= _neighborSize )
				{
					_someGraph.addEdge(srcID,neiID);
				}  
			}
			// calculation of angle
			else if(plc%2)
			{
				if(sumY > 0 && (plc+_neighborSize/2) > _neighborSize)
				{
					_someGraph.addEdge(srcID,neiID);					
				}
				else if(sumY < 0 && (plc+_neighborSize/2) < _neighborSize)
				{
					_someGraph.addEdge(srcID,neiID);
				}

			}			
		}
	}

}

//=============================================================================
//	get source  vertex id   and place in maybe edge vertex
void GameController::ElectricityHexdr(const int srcID,const int plc)
{
	// get vertex position 
	const float srcX = _someGraph.getData(srcID)->getX();
	const float srcY = _someGraph.getData(srcID)->getY();

	// get all posible nieghbors from full graph
	Graph<Vertex>::NeighborIterator<Vertex> it2(_FullGraph,srcID);
	
	// for all neighbors - comper between potential edges, depend on angle
	for(;it2 != it2.end();it2++)
	{
		const int neiID =   (*it2)->GetID();
		const vector<bool> _futedgesS = _someGraph.getData(neiID)->getFutEdg();

		// if some posible angle in posibel edge exist.
		if(_futedgesS[(plc+(_neighborSize/2))%_neighborSize])
		{
			const float neX = _someGraph.getData(neiID)->getX();
			const float neY = _someGraph.getData(neiID)->getY();
		
			const float sumX = neX - srcX;
			const float sumY = neY - srcY;
			// calculation of angle
			if(plc%3 == 0){	
				if(sumX < 0 && sumY==0 && (plc+_neighborSize/2) < _neighborSize  ){
					_someGraph.addEdge(srcID,neiID);					
				}
			}
			else if(plc%3 == 2){
				if(sumY > 0 && sumX < 0 && (plc+_neighborSize/2) > _neighborSize){
					_someGraph.addEdge(srcID,neiID);					
				}
			}	
			else if(plc%3 == 1)
			{
				if(sumY > 0 && sumX > 0 && (plc+_neighborSize/2) > _neighborSize){
					_someGraph.addEdge(srcID,neiID);					
				}
			}
		}
	}

}
//=============================================================================
// function thatm manage all potential edges for each vertex in the graph
void GameController::FindElectrecisty()
{
	// Start put real edges
	Graph<Vertex>::GraphIterator<Vertex> it1(_someGraph);
	for(;it1 != it1.end() ;it1++)
	{		
		const vector<bool> _futedges = (*it1)->getFutEdg();

		const int vec_Size = (int)_futedges.size();

		// for each vertex - light what nedded
		for(int i=0;i<vec_Size;i++)
		{
			if(_futedges[i])
			{
				if(_grKind == Quad)
					ElectricityQuadr((*it1)->GetID(),i);
				else if(_grKind == Hexagonal)
					ElectricityHexdr((*it1)->GetID(),i);
				  
			}
		}	
	}

}

//=============================================================================
// the function which provide resize window
void GameController::resizeWindow(int w, int h)
{
	_WindowHeight = (h>1) ? h : 2;
	_WindowWidth = (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Always view [0,1]x[0,1].
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//=============================================================================
// the function which load call back for glut 
void GameController::LoadCallBacksForGlut()
{
	glutIdleFunc(idle);
	glutDisplayFunc(display);  
	glutMouseFunc (mouseButton);
	glutKeyboardFunc(KeyPress);
	CreateMenuForGlut();
}


//=============================================================================
//	Dispaly function
void GameController::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut
	glPointSize(_pointSize);
	
	// if not solution - we show the real time game graph
	if(!_show_sol)
	{
		Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
		for(;it != it.end() ;it++)
		{
			(*it)->Draw();
			(*it)->LightOFF();		
		}	
	}
	else					
	{
		//	Show solution graph for player if hi dont want play this level
		Graph<Vertex>::GraphIterator<Vertex> it(_Solution);
		for(;it != it.end() ;it++)
		{
			(*it)->Draw();		
		}
	}
	// time of game update
	if(_update_timer)
	{
		seconds = time(NULL);
	}
	// text on board menegment
	sprintf_s(timer,"LEVEL:%d          Game time: %d.",_level+1,seconds-time_game);
	glutPrint(0.02f, 0.97f, timer, 0.0f, 1.0f, 0.0f, 0.5f);
	

	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut

}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	// we call the display function
	display();	

	// initiation of  graph BFS
	vector<int> _BFS = _someGraph.getVectorOfIdsBFS(_ID_OF_CENTER_VERTEX);
	const int vecSize =	 (int)_BFS.size();
	
	// chek if it the end of the game
	if(vecSize == _someGraph.countNodes())
	{
		_update_timer = false;
	}
	// lights up all the vertexes at BFS tree
	for(int i=0;i<vecSize;i++)
	{
		_someGraph.getData(_BFS[i])->LightON();
	}			
	
}
