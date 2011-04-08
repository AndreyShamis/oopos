#include "GameController.h"
//=============================================================================
GameController *GameController::_instance = NULL;

//=============================================================================


graphKind	GameController::_grKind = Quad;
int			GameController::_grSize = 9;

int	GameController::_WindowHeight;
int	GameController::_WindowWidth;
int	GameController::_ID_OF_CENTER_VERTEX = 0;
Graph<Vertex>  GameController::_someGraph;
Graph<Vertex>  GameController::_FullGraph;
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


	createFullGraph(); 
	_FullGraph = _someGraph;

}

//=============================================================================
//
void GameController::createFullGraph()
{
	if(_grKind == Quad)
		creatQuadGraph(5);
	else
		//creatHexagonalGraph();
		;


	///	Looking for rundom DFS vertex
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	int StartVertex =  rand()%_someGraph.countNodes();
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
					if(_someGraph.NeighborsCount(DFS[i]) >1 )
					{
						if(rand()%2 != 1)
							found = true;
					}
					else
					{
						found = true;
					}

					break;
				}

			}

			if(found)
			{
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
		_someGraph.addEdge(_back_adg[i].vert1,_back_adg[i].vert2 );

		int sosedi = (int)_someGraph.NeighborsCount(_back_adg[i].vert1);

		_someGraph.getData(_back_adg[i].vert1)->ChangeEdge(sosedi);

		sosedi = (int)_someGraph.NeighborsCount(_back_adg[i].vert2);
		_someGraph.getData(_back_adg[i].vert2 )->ChangeEdge((sosedi+2)%4);



	}


	//				float distY=_someGraph.getData(DFS[i])->getY()-_someGraph.getData(DFS[j])->getY();
	//				float distX =_someGraph.getData(DFS[i])->getX()-_someGraph.getData(DFS[j])->getX();
	//				float dist = sqrt(distX*distX + distY*distY);
	//				//cout << "Distan:" << dist << "\n";

	//				cout  << "Sin:"<< sin((distX)/dist) << "\tCos:" << cos(distY/dist) <<  "\n";
	//				if(distX)
	//					cout << tan(distY*3.14/distX)/180;
	//				else
	//					cout << "0";
	//				cout << "\n";


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
			
			_someGraph.getData(id)->SetID(id);
            //newVertex.SetID(id);
            if(prev_id)
				_someGraph.addEdge(prev_id,id);

            if(i)
				_someGraph.addEdge(id-rowSize,id);

            prev_id=id;
               
			if((rowSize+1)/2 == i && (col_size+1)/2 == j)
				_ID_OF_CENTER_VERTEX = id;
        }

    }   

	//cout << _someGraph.countEdges() << "---------\n";
}

//=============================================================================
// the function which provide mouse button
void GameController::mouseButton(int button, int state, int x, int y)
{
	if(button == 0 && state == 1)
	{
		float xPos = ((float)x)/((float)(_WindowWidth-1));
		float yPos = ((float)y)/((float)(_WindowHeight-1));
		yPos = 1.0f-yPos;

	//cout << "X: " << xPos << "\t Y: " << yPos << "\n";

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
		_someGraph.getData(id)->Shift();
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
}

//=============================================================================
//	Dispaly function
void GameController::display()
{
	glClear(GL_COLOR_BUFFER_BIT );				//	Glut

	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);

	for(;it != it.end() ;it++)
	{
		(*it)->Draw();
		
	}

	glFlush() ;									//	Glut
	glutSwapBuffers();							//	Glut

}

//=============================================================================
//	Idle function 
void GameController::idle()
{

	//if(_GameMod == _PLAY)
		display();			//	call display function

	//if(_GameMod == _MANU)
	//	;
}
