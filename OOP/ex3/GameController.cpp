#include "GameController.h"
//=============================================================================
GameController *GameController::_instance = NULL;

//=============================================================================


graphKind	GameController::_grKind = Quad;
int			GameController::_grSize = 9;
int			GameController::_level = 0;

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
GameController::GameController()
{
	srand ( time(NULL) );
	glMatrixMode(GL_PROJECTION);		//	Glut
    glLoadIdentity();					//	Glut
    gluOrtho2D(0, 600, 0, 600);			//	Glut 
	

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


	_show_sol = false;
	createFullGraph(); 
	_Solution = _someGraph;
	FindElectrecisty();

	
}

//=============================================================================
//
void GameController::createFullGraph()
{
	if(_grKind == Quad)
	{
		creatQuadGraph(5+_level*2);
	}
	else
		//creatHexagonalGraph();
		;

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
	for(int i=0;i<(int)DFS.size();i++)
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

	for(int i=0;i<(int)DFS.size();i++)
	{
		_someGraph.detachVertex(DFS[i]);
	}

	for(int i=0;i<(int)_back_adg.size();i++)
	{
		//_someGraph.addEdge(_back_adg[i].vert1,_back_adg[i].vert2 );

		if(_someGraph.getData(_back_adg[i].vert1)->getX() > _someGraph.getData(_back_adg[i].vert2)->getX())
		{   
			_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(0);
			_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(2);
		}
		else if(_someGraph.getData(_back_adg[i].vert1)->getX() < _someGraph.getData(_back_adg[i].vert2)->getX())
		{
			_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(2);
			_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(0);
		}

		else if(_someGraph.getData(_back_adg[i].vert1)->getY() > _someGraph.getData(_back_adg[i].vert2)->getY())
		{   
			_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(1);
			_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(3);
		}
		else if(_someGraph.getData(_back_adg[i].vert1)->getY() < _someGraph.getData(_back_adg[i].vert2)->getY())
		{
			_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(3);
			_someGraph.getData(_back_adg[i].vert2)->ChangeEdge(1);
		}
		/*

		int sosedi = (int)_someGraph.NeighborsCount(_back_adg[i].vert1);

		_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(sosedi);

		sosedi = (int)_someGraph.NeighborsCount(_back_adg[i].vert2);
		_someGraph.getData(_back_adg[i].vert2)->ChangeEdge((sosedi+2)%3);


		  */
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
//
void GameController::creatQuadGraph(const int rowSize)
{
	
	int id			= 0;
	float x			= 0;
	float y			= 0;
	int prev_id		= 0;
    int col_size = rowSize;

    Vertex newVertex(x,y,4,(1-0.2)/rowSize);

    for(int i= 0; i< rowSize;i++)
    {
        prev_id=0;
        for(int j= 0; j< col_size;j++)
        {
            float x = (float)(i+1)*(1-0.2)/rowSize;
            float y = (float)(j+1)*(1-0.2)/col_size;
            Vertex newVertex(x,y,4,(1-0.2)/rowSize);
            int id =_someGraph.addVertex(newVertex);
			
			//_Solution.addVertex(newVertex);			
			//_Solution.getData(id)->SetID(id);
			_someGraph.getData(id)->SetID(id);
            //newVertex.SetID(id);
            if(prev_id)
				_someGraph.addEdge(prev_id,id);

            if(i)
				_someGraph.addEdge(id-rowSize,id);

            prev_id=id;
               
			if((rowSize-1)/2 == i && (col_size-1)/2 == j)
				_ID_OF_CENTER_VERTEX = id;
        }

    }   

	//cout << _someGraph.countEdges() << "---------\n";
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
		
		Graph<Vertex>::GraphIterator<Vertex> detach(_someGraph);
		for(;detach != detach.end() ;detach++)
		{
			_someGraph.detachVertex((*detach)->GetID());
		}
							
		//	Looking For Pressed Vertex
		Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
		float resx = 10;
		float resy = 10;
		int id = 0;
		for(;it != it.end() ;it++)
		{
			float vertX = (*it)->getX();
			float vertY = (*it)->getY();

			 if(abs(vertX-xPos) <=  resx && abs(vertY-yPos) <= resy)
			 {
				 resx = abs(vertX-xPos) ;
				 resy = abs(vertY-yPos);
				id = (*it)->GetID();
			}
		}
		//	End pressed Vertex
		_someGraph.getData(id)->Shift();	//	Shift the vertex

		FindElectrecisty();
		
	}
}


void GameController::FindElectrecisty()
{
// Start put real edges
	Graph<Vertex>::GraphIterator<Vertex> it1(_someGraph);
	for(;it1 != it1.end() ;it1++)
	{		
		vector<bool> _futedges = (*it1)->getFutEdg();
		for(int i=0;i<_futedges.size();i++)
		{
			if(_futedges[i])
			{
				Graph<Vertex>::NeighborIterator<Vertex> it2(_FullGraph,(*it1)->GetID());
				for(;it2 != it2.end();it2++)
				{
					vector<bool> _futedgesS = _someGraph.getData((*it2)->GetID())->getFutEdg();
					if(_futedgesS[(i+2)%4] 
					&& ((*it1)->getX() >= (*it2)->getX() || (*it1)->getY() <= (*it2)->getY()) 
					&&  !((*it1)->getX() >= (*it2)->getX() && (*it1)->getY() <= (*it2)->getY()) )
					{
						_someGraph.addEdge((*it1)->GetID(),(*it2)->GetID());
						break;
					}
				}
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
	for(int i=0;i<_BFS.size();i++)
	{
		_someGraph.getData(_BFS[i])->LightON();
	}

	//if(_GameMod == _PLAY)
		display();			//	call display function

	//if(_GameMod == _MANU)
	//	;
}
