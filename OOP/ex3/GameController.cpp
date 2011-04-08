#include "GameController.h"
//=============================================================================
GameController *GameController::_instance = NULL;

//=============================================================================


graphKind	GameController::_grKind = Quad;
int			GameController::_grSize = 9;

int	GameController::_WindowHeight;
int	GameController::_WindowWidth;
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

	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);
	//GraphIterator<Vertex> it(&someGraph);
	//GraphIterator<Vertex> it(&someGraph);

	for(;it != it.end() ;it++)
	{
		cout << "Ya ";// <<;
		cout << (*it)->GetID() << "\n";

	}
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
	Graph<Vertex>::GraphIterator<Vertex> it(_someGraph);

	int StartVertex =  rand()%_someGraph.countNodes();
	int i=0;
	for(;it != it.end() ;it++)
	{

		if(StartVertex == i)
		{
			StartVertex = (*it)->GetID();
		}
		i++;
	}

	
	//Graph<Vertex>::DFSIterator<Vertex> nei(_someGraph,StartVertex);
	//for(;nei != nei.end() ;nei++)
	//{
	//	Graph<Vertex>::NeighborIterator<Vertex> nei(_someGraph,(*it)->GetID());
	//	for(;nei != nei.end() ;it++)
	//	{
	//		cout << " - " << (*nei)->GetID();
	//	}

	//	cout << " - " << (*nei)->GetID();

	//}
	//cout << "\n";

	vector<int> DFS = _someGraph.getVectorOfIdsDFS(StartVertex);

	for(int i =1;i<(int)DFS.size();i++)
	{
		Graph<Vertex>::NeighborIterator<Vertex> nei(_someGraph,DFS[i]);
		for(;nei != nei.end() ;nei++)
		{
			for(int j = i-1;j>=0;j--)
			{
				if(DFS[j] == DFS[i])
				{
					cout << tan(_someGraph.getData(DFS[i])->getY()-_someGraph.getData(DFS[j])->getY()/(_someGraph.getData(DFS[i])->getX()-_someGraph.getData(DFS[j])->getX()));
					cout << "\n";
					break;
				}
			}
			//cout << " - " << (*nei)->GetID();
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

	cout << "Start\n";
    for(int i= 0; i< rowSize;i++)
    {
        prev_id=0;
        for(int j= 0; j< col_size;j++)
        {
            float x = (float)(i+1)*(1-0.2)/rowSize;
            float y = (float)(j+1)*(1-0.2)/col_size;
            Vertex newVertex(x,y,4);
            int id =_someGraph.addVertex(newVertex);

            newVertex.SetID(id);
            if(prev_id)
				_someGraph.addEdge(prev_id,id);

            if(i)
				_someGraph.addEdge(id-rowSize,id);

            prev_id=id;
                
        }

    }   
	//int **matr = _someGraph.getMatrixRepresentation();

	//for(int i=0;i<_someGraph.countNodes()+1;i++)
	//{
	//	for(int j=0;j<_someGraph.countNodes()+1;j++)
	//		cout  << setw(2) << matr[i][j];

	//	cout << "\n";

	//}
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

	cout << "X: " << xPos << "\t Y: " << yPos << "\n";

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
		//	 cout << "-ID: " << (*it)->GetID() << "::" << vertX << " " << vertY << " " << abs(vertX-xPos) << " " <<  abs(vertY-yPos) << "\n";

		 }
		// else
		// {
		//	 cout << "ID: " << (*it)->GetID() << "::" << vertX << " " << vertY << " " << abs(vertX-xPos) << " " <<  abs(vertY-yPos) << "\n";
		// }
		 
		//if( resx < 1/5 && resy < 1/5)
		//{
		//	cout << "Found:" << (*it)->GetID() << "\n"; 
		//}
		//cout << resx << "   " << resy << "\n";
		//Graph<Vertex>::NeighborIterator<Vertex> nei(_someGraph,(*it)->GetID());
		//for(;nei != nei.end() ;it++)
		//{
		//	cout << " - " << (*nei)->GetID();
		//}
		//cout << "\n";
	}
	cout << "Found:" << id << "\n"; 
	//Paint::getInst()->mouseButton(button,state,xPos,yPos);
	}
}

//=============================================================================
// the function which provide  select from menu
void GameController::selectFromMenu(int commandId)
{
	//Paint::getInst()->selectFromMenu(commandId);
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
	//glutKeyboardFunc(KeyPress);

	//	Sound Play
	//sndPlaySound(L"SOUND/BackGround_Sound.wav", SND_LOOP | SND_ASYNC );
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
		//Graph<Vertex>::NeighborIterator<Vertex> nei(_someGraph,(*it)->GetID());
		//for(;nei != nei.end() ;it++)
		//{
		//	cout << " - " << (*nei)->GetID();
		//}
		//cout << "\n";
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
