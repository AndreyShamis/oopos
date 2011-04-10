#include "GameController.h"
//=============================================================================
GameController *GameController::_instance = NULL;

//=============================================================================


graphKind	GameController::_grKind = Quad;
int			GameController::_grSize = 9;
int			GameController::_level = 0;
time_t GameController::time_game = 0;
short int	GameController::_neighborSize = 0;
int	GameController::_WindowHeight;
int	GameController::_WindowWidth;
int	GameController::_ID_OF_CENTER_VERTEX = 0;
Graph<Vertex>  GameController::_someGraph;
Graph<Vertex>  GameController::_FullGraph;
Graph<Vertex>  GameController::_Solution;

bool GameController::_show_sol = false;

//=============================================================================
//	Return pointer to created? class-object
GameController *GameController::getInst()
{
	if(_instance == NULL)					//	if not created create it
		_instance = new GameController();

	return(_instance);						//	Return the object pointer 

}
//=============================================================================
// the function which provide key press
void GameController::KeyPress(unsigned char key, int x, int y)
{
	
	if(key == 'x')
		exit(EXIT_SUCCESS);
	else if(key == 'n')
	{
		ClearAll();
		createGameGraph();	
	}
	else if(key == 'l')
	{
		_level++;
		ClearAll();
		createGameGraph();	
	}
	else if(key == 's')
	{
		_show_sol = true;
	}
	else if(key == 'q')
	{
		_grKind = Quad;
		ClearAll();
		createGameGraph();	

	}
	else if(key == 'h')
	{
		_grKind = Hexagonal;

		ClearAll();
		createGameGraph();	

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
	_GameMod = _MENU;
}
//=============================================================================
void GameController::LoadGame()
{
	glutReshapeFunc(resizeWindow);
	LoadCallBacksForGlut();
	createGameGraph();

}

//=============================================================================
//
void GameController::createGameGraph()
{

  time_t seconds;

  seconds = time (NULL);

  if(time_game)
  {
		printf ("Game second", (seconds-time_game));
  }
	  time_game = seconds   ;
	_show_sol = false;
	createFullGraph(); 
	_Solution = _someGraph;
	GraphGrinder();
	FindElectrecisty();	
}

void GameController::GraphGrinder()
{
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	//int StartVertex =  rand()%(_someGraph.countNodes()-1);
	//int i=0;
	for(;it != it.end() ;it++)
	{
		const int rnd = rand()%4;

		for(int i=0;i<rnd;i++)
		{
			(*it)->Shift();
		}
			
	}
}
//=============================================================================
//
void GameController::creatQuadGraph(const int rowSize)
{
	
	int id			= 0;
	float x			= 0;
	float y			= 0;
	int prev_id		= 0;
    int col_size = rowSize;

    for(int i= 0; i< rowSize;i++)
    {
        prev_id=0;
        for(int j= 0; j< col_size;j++)
        {
            float x = (float)(i+1)*(1-0.2)/rowSize;
            float y = (float)(j+1)*(1-0.2)/col_size;
            Vertex newVertex(x,y,4,(1-0.2)/rowSize);
            int id =_someGraph.addVertex(newVertex);
			
			_someGraph.getData(id)->SetID(id);
            if(prev_id)
				_someGraph.addEdge(prev_id,id);

            if(i)
				_someGraph.addEdge(id-rowSize,id);

            prev_id=id;
               
			if((rowSize-1)/2 == i && (col_size-1)/2 == j)
				_ID_OF_CENTER_VERTEX = id;
        }

    }   
}
//=============================================================================
//
void GameController::creatHexagonalGraph(const int size)
{
	vector<int> _layer;
	vector<int> _layer_new;
	int start = 2  ;
	float dist	= (1-0.23)/(2*size);
	for(int i =0;i<size;i++)
	{
		int id_prev = 0; 
		for(int j=start;j<2*size-1-start;j+=2)
		{
			float x = (float)(_level+1)*dist + float(j+1)*dist;
			float y = (float)(_level+1)*dist+ 1.8*((i+1-(float)(i*0.05)))*dist;
			Vertex newVertex(x,y,6,dist*2);
			int id = _someGraph.addVertex(newVertex);
			_someGraph.getData(id)->SetID(id);

			_layer_new.push_back(id);
			if((size-1)/2 == i && (size-1) == j )
			{
				_ID_OF_CENTER_VERTEX = id;
			}
			if(id_prev)
			{
				_someGraph.addEdge(id,id_prev);
			}
			id_prev = id;
		}

		if(i<(size+1)/2)
		{
			for(int is=0;is<_layer.size();is++)
			{
				_someGraph.addEdge(_layer[is],_layer_new[is]);
				_someGraph.addEdge(_layer[is],_layer_new[is+1]);

			}
		
		}
		else
		{
			for(int is=0;is<_layer_new.size();is++)
			{
				_someGraph.addEdge(_layer_new[is],_layer[is]);
				_someGraph.addEdge(_layer_new[is],_layer[is+1]);

			}		
		}

		if(i<(size-1)/2){
			start--;
		}
		else{
			start++;	
		}
		_layer = _layer_new;
		_layer_new.clear();

	}

}
//=============================================================================
//
void GameController::createFullGraph()
{
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
	_FullGraph = _someGraph;

	///	Looking for rundom DFS vertex
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	int StartVertex =  rand()%(_someGraph.countNodes()-1);
	int i=0;
	for(;it != it.end() ;it++)
	{
		if(StartVertex == i)
		{
			StartVertex = (*it)->GetID();
			break;
		}
		i++;
	}

	// Get vector of ids by DFS
	vector<int> DFS = _someGraph.getVectorOfIdsDFS(StartVertex);

	vector<AddEdges> _back_adg;
	const int vecSize0 =	  (int)DFS.size();

	for(int i=0;i<vecSize0;i++)
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
	const int vecSize = (int)DFS.size();
	for(int i=0;i<vecSize;i++)
	{
		_someGraph.detachVertex(DFS[i]);
	}


	const int vecSize2 =(int)_back_adg.size(); 
	for(int i=0;i<vecSize2;i++)
	{

		const float vert1X	= _someGraph.getData(_back_adg[i].vert1)->getX() ;
		const float vert1Y  = _someGraph.getData(_back_adg[i].vert1)->getY();
		const float vert2X  = _someGraph.getData(_back_adg[i].vert2)->getX();
		const float vert2Y	 =_someGraph.getData(_back_adg[i].vert2)->getY();
		
		if(_grKind == Quad)
		{
			if(vert1X>vert2X)
			{   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(0);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(2);
			}
			else if(vert1X<vert2X)
			{
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(2);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(0);
			}

			else if(vert1Y>vert2Y)
			{   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(1);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(3);
			}
			else if(vert1Y<vert2Y)
			{
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(3);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(1);
			}
		}
		else if(_grKind == Hexagonal)
		{
			if(vert1X > vert2X && vert1Y > vert2Y)
			{   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(1);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(4);
			}
			else if(vert1X < vert2X && vert1Y < vert2Y)
			{  
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(4);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(1);
			}
			else  if(vert1X > vert2X && vert1Y == vert2Y)
			{
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(0);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(3);

			}
			else  if(vert1X < vert2X && vert1Y == vert2Y)
			{
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(3);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(0);

			}
			else if(vert1X > vert2X && vert1Y < vert2Y)
			{   
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(5);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(2);
			}
			else if(vert1X < vert2X && vert1Y > vert2Y)
			{  
				_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(2);
				_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(5);
			}			
		}
	}
}

void GameController::ClearAll()
{
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	cout << "Start delete...\n";
	for(;it != it.end() ;it++)
	{
		_someGraph.removeVertex((*it)->GetID());
	}
	_FullGraph = _someGraph;
	_Solution = _someGraph;
	cout << "Finish delete!\n";

}



//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
{
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

	const vector<int> _vec =  _someGraph.getVectorOfIdsBFS(_ID_OF_CENTER_VERTEX);
	if(_vec.size() == _someGraph.countNodes())
	{

		_level++;
		ClearAll();
		createGameGraph();

	}
}


//	get source  vertex id   and place in maybe edge vertex
void GameController::ElectricityQuadr(const int srcID,const int plc)
{

	const float srcX = _someGraph.getData(srcID)->getX();
	const float srcY = _someGraph.getData(srcID)->getY();
	
	Graph<Vertex>::NeighborIterator<Vertex> it2(_FullGraph,srcID);
	
	for(;it2 != it2.end();it2++)
	{
		const int neiID =   (*it2)->GetID();
		const vector<bool> _futedgesS = _someGraph.getData(neiID)->getFutEdg();

		if(_futedgesS[(plc+(_neighborSize/2))%_neighborSize])
		{
			const float neX = _someGraph.getData(neiID)->getX();
			const float neY = _someGraph.getData(neiID)->getY();
		
			const float sumX = neX - srcX;
			const float sumY = neY - srcY;
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


//	get source  vertex id   and place in maybe edge vertex
void GameController::ElectricityHexdr(const int srcID,const int plc)
{

	const float srcX = _someGraph.getData(srcID)->getX();
	const float srcY = _someGraph.getData(srcID)->getY();
	
	Graph<Vertex>::NeighborIterator<Vertex> it2(_FullGraph,srcID);
	
	for(;it2 != it2.end();it2++)
	{
		const int neiID =   (*it2)->GetID();
		const vector<bool> _futedgesS = _someGraph.getData(neiID)->getFutEdg();

		if(_futedgesS[(plc+(_neighborSize/2))%_neighborSize])
		{
			const float neX = _someGraph.getData(neiID)->getX();
			const float neY = _someGraph.getData(neiID)->getY();
		
			const float sumX = neX - srcX;
			const float sumY = neY - srcY;
			if(plc%3 == 0)
			{	
				if(sumX < 0 && sumY==0 && (plc+_neighborSize/2) < _neighborSize  )
				{
					_someGraph.addEdge(srcID,neiID);					
				}
				//else if(sumX < 0 &&sumY==0  && (plc+_neighborSize/2) >= _neighborSize )
				//{
				//	;//_someGraph.addEdge(srcID,neiID);
				//}  
			}
			else if(plc%3 == 2)
			{
				if(sumY > 0 && sumX < 0 && (plc+_neighborSize/2) > _neighborSize)
				{
					_someGraph.addEdge(srcID,neiID);					
				}
				//else if(sumY < 0 && (plc+_neighborSize/2) < _neighborSize)
				//{
				//	;//_someGraph.addEdge(srcID,neiID);
				//}

			}	
			else if(plc%3 == 1)
			{

				if(sumY > 0 && sumX > 0 && (plc+_neighborSize/2) > _neighborSize)
				{
					_someGraph.addEdge(srcID,neiID);					
				}
			}
		}
	}

}

void GameController::FindElectrecisty()
{
	// Start put real edges
	Graph<Vertex>::GraphIterator<Vertex> it1(_someGraph);
	for(;it1 != it1.end() ;it1++)
	{		
		const vector<bool> _futedges = (*it1)->getFutEdg();

		const int vec_Size = (int)_futedges.size();

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
}


//=============================================================================
//	Dispaly function
void GameController::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

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
		Graph<Vertex>::GraphIterator<Vertex> it(_Solution);
		for(;it != it.end() ;it++)
		{
			(*it)->Draw();
			//(*it)->LightOFF();		
		}
	}
	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut

}

//=============================================================================
//	Idle function 
void GameController::idle()
{
	//Graph<Vertex>::BFSIterator<Vertex> it(_someGraph,_ID_OF_CENTER_VERTEX);

	vector<int> _BFS = _someGraph.getVectorOfIdsBFS(_ID_OF_CENTER_VERTEX);
	const int vecSize =	 (int)_BFS.size();
	
	for(int i=0;i<vecSize;i++)
	{
		_someGraph.getData(_BFS[i])->LightON();
	}

	//if(_GameMod == _PLAY)
		display();			//	call display function

	//if(_GameMod == _MANU)
	//	;
}
