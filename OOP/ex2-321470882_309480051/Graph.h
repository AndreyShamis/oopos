#pragma once
#include <vector>
#include <queue>
#include "macros.h"
#include "hadassahgraph.h"
using namespace std;


#define MAX_DEFAULT_SIZE_CAN_BE 99999999

template <class T> 
class Graph : public HadassahGraph<T>
{
	enum VertexState { White, Gray, Black };


	struct SomeNode
	{
		int				_Node_id;
		vector <int>	_neighbors;	//	vecto which conation id`s of neighbors
	};
public:
	Graph();
	int		addVertex(const T data);
	bool	removeVertex(int vertexId);
	bool	addEdge(int vertexId1, int vertexId2);
	bool	removeEdge(int vertexId1, int vertexId2);
	bool	edgeExists(int vertexId1, int vertexId2) const;
	const T* const getData(int vertexId);
	int		countEdges() const;
	int		countNodes() const;
	int		**getMatrixRepresentation() const;
	void	printBFS(int sourceId) const;
	void	printDFS(int sourceId) const;
	bool	detachVertex(int vertexId); 

	//	Futures function 
	void	setUniq_values(const bool newValue);
	int		getIDbyValue(const T data)const;
private:

	vector <T>			_db;
	vector <SomeNode>	_ids;
	unsigned int		_max_size_can_be;
	unsigned int		_counter;
	bool				_Graph_ValuesUniqe;
	
	int		getVectorPos(const int Uniq_ID) const;
	void	DeleteAll_Neighbors(const int VertexAxactPosition);
	void	DeleteNeighborByID(const int SelfID,const int NeighborID);
	bool	HaveEdge(const int SelfID,const int NeighborID)const;
	void	runDFS(int u, VertexState state[]) const;

};

//=============================================================================
//=============================================================================
//=============================================================================

template <class T> 
Graph<T>::Graph()
{
	_max_size_can_be	= MAX_DEFAULT_SIZE_CAN_BE;
	_counter			=	0;
	_Graph_ValuesUniqe	=	false;
}  

//=============================================================================
template <class T> 
int	Graph<T>::getIDbyValue(const T data)const
{
	const int VertexCount = countNodes();

	for(int i=0;i<VertexCount;i++)
	{
		if(_db[i] == data)
		{
			return(_ids[i]._Node_id);
		}
	}
	return(0);
}

//=============================================================================
template <class T> 
void Graph<T>::setUniq_values(const bool newValue)
{
	if(countNodes() == 0)
		_Graph_ValuesUniqe = newValue;
	else if(countNodes() != 0 && _Graph_ValuesUniqe && !newValue)
		_Graph_ValuesUniqe = newValue;
}
//=============================================================================

/* Adds a vertex to the graph *
 * Returns unique vertex id   */
template <class T> 
int Graph<T>::addVertex(const T data)
{
	if(_Graph_ValuesUniqe && getIDbyValue(data))
	{
		return(0);
	}
	_counter++;
	_db.push_back(data);

	SomeNode newNode;
	newNode._Node_id = _counter;
	_ids.push_back(newNode);
	
	return(_counter);
}

//=============================================================================
template <class T> 
int Graph<T>::getVectorPos(const int Uniq_ID) const
{
		
	const int Vertex_Size = _ids.size();

	for(int i=0;i<Vertex_Size;i++)
	{
		if(_ids[i]._Node_id == Uniq_ID)
			return(i+1);
	}

	return(0);
}

//=============================================================================
template <class T> 
bool Graph<T>::HaveEdge(const int SelfID,const int NeighborID)const
{
		
	const int Neighbors_Size = _ids[SelfID]._neighbors.size();

	for(int i=0;i<Neighbors_Size;i++)
	{
		if(_ids[SelfID]._neighbors[i] == NeighborID)
			return(true);
	}

	return(false);
}

//=============================================================================
template <class T> 
void Graph<T>::DeleteAll_Neighbors(const int VertexAxactPosition)
{
	const int Neighbors_Size = _ids[VertexAxactPosition]._neighbors.size();
	
	for(int i = 0; i<Neighbors_Size;i++)
	{
		if(_ids[VertexAxactPosition]._neighbors[i] != _ids[VertexAxactPosition]._Node_id)
			DeleteNeighborByID(VertexAxactPosition,_ids[VertexAxactPosition]._neighbors[i]);
	}

	_ids[VertexAxactPosition]._neighbors.clear();

}
//=============================================================================
template <class T> 
void Graph<T>::DeleteNeighborByID(const int SelfID,const int NeighborID)
{

	const int Neighbor = getVectorPos(NeighborID);

	if(Neighbor)
	{
		for(int j=0;j < (int)_ids[Neighbor-1]._neighbors.size();j++)
		{
			if(_ids[Neighbor-1]._neighbors[j] == _ids[SelfID]._Node_id)
			{
				_ids[Neighbor-1]._neighbors.erase(_ids[Neighbor-1]._neighbors.begin()+j);
				j--;
				break;
			}
		}
	}


}
//=============================================================================
/* Removes a vertex with id= vertexId       *
*  Returns false if vertex does not exists  */
template <class T> 
bool Graph<T>::removeVertex(int vertexId)
{
	const int Uniq_Pos = getVectorPos(vertexId);

	if(Uniq_Pos)
	{
		DeleteAll_Neighbors(Uniq_Pos-1);
		_db.erase(_db.begin()+Uniq_Pos-1);
		_ids.erase(_ids.begin()+Uniq_Pos-1);
		return(true);
	}

	return(false);
}

//=============================================================================
/* Adds an edge between vertexId1 and vertexId2          *
*  Returns false if one of the vertices does not exists  */
// TODO check if have edge need to do
template <class T>
bool Graph<T>::addEdge(int vertexId1, int vertexId2)
{
	const int First_Pos		=	getVectorPos(vertexId1);
	const int Second_Pos	=	getVectorPos(vertexId2);
	
	if(First_Pos && Second_Pos && First_Pos != Second_Pos && !HaveEdge(First_Pos-1,vertexId2))
	{
		_ids[First_Pos-1]._neighbors.push_back(vertexId2);
		_ids[Second_Pos-1]._neighbors.push_back(vertexId1);
		return(true);
	}
	else if(First_Pos && First_Pos == Second_Pos && !HaveEdge(First_Pos-1,vertexId1))
	{
		_ids[First_Pos-1]._neighbors.push_back(vertexId1);
		return(true);
	}

	return(false);
}

//=============================================================================
/* Removes an edge between vertexId1 and vertexId2       *
*  Returns false if one of the vertices does not exists  */
template <class T>
bool Graph<T>::removeEdge(int vertexId1, int vertexId2)
{
	const int First_Pos		=	getVectorPos(vertexId1);
	const int Second_Pos	=	getVectorPos(vertexId2);
	
	if(First_Pos && Second_Pos && First_Pos != Second_Pos)
	{
		DeleteNeighborByID(First_Pos-1,vertexId2);
		DeleteNeighborByID(Second_Pos-1,vertexId1);
		return(true);
	}
	else if(First_Pos && Second_Pos && First_Pos == Second_Pos)
	{
		DeleteNeighborByID(First_Pos-1,vertexId1);
		return(true);
	}

	return(false);
}

//=============================================================================
/* Check if an edge exists in the graph                                      *
*  Returns false if one of the vertices does not exists or there is no edge  */
template <class T>
bool Graph<T>::edgeExists(int vertexId1, int vertexId2) const
{
	const int First_Pos		=	getVectorPos(vertexId1);
	const int Second_Pos	=	getVectorPos(vertexId2);

	if(First_Pos && Second_Pos && First_Pos != Second_Pos)
	{
		if(HaveEdge(First_Pos-1,vertexId2) &&	HaveEdge(Second_Pos-1,vertexId1))
			return(true);
	}
	else if(First_Pos && First_Pos == Second_Pos)
	{
		if(HaveEdge(First_Pos-1,vertexId1))
			return(true);
	}

	return(false);
}

//=============================================================================
/* Get the data of a vertex in the graph                        *
*  Returns the data of type T, NULL if vertex does not exists.  */
template <class T>
const T* const Graph<T>::getData(int vertexId)
{
	const int Ver_Pos		=	getVectorPos(vertexId);
	T			*s			=	NULL;

	if(Ver_Pos)
		s = &_db[Ver_Pos-1];

	return(s);
}

//=============================================================================
/* Count graph edges                         *
*  Returns the number of edges in the graph  */
template <class T>
int Graph<T>::countEdges() const
{
	const int Vertex_Size = _ids.size();
	int return_value = 0;

	//	Farej rulez 
	for(int i =0;i<Vertex_Size;i++)
		for(int j=i;j<Vertex_Size;j++)
		{
			if(edgeExists(_ids[i]._Node_id,_ids[j]._Node_id))
				return_value++;
		}

	return(return_value);
}

//=============================================================================
/* Count graph vertices                         *
*  Returns the number of vertices in the graph  */
template <class T>
int Graph<T>::countNodes() const
{
	const int count = (int)_db.size();
	return(count);
}

//=============================================================================
/* Get the matrix representation of the graph   *
*  Returns an int matrix .                      */
template <class T>
int** Graph<T>::getMatrixRepresentation() const
{

	const int Row_Size = 1+_db.size();
	int **cols=NULL;

	cols = new(std::nothrow) int*[Row_Size];

	if(cols != NULL)
		for(int i=0;i<Row_Size;i++)
		{
			cols[i] = new (std::nothrow) int[Row_Size];
			if(cols[i] == NULL)
			{
				cerr << "Can`t allocate memory\n";
				exit(EXIT_FAILURE);
			}
		}
	else
	{
		cerr << "Can`t allocate memory\n";
		exit(EXIT_FAILURE);
	}


	cols[0][0] = Row_Size -1;

	for(int i =1;i<Row_Size;i++)
	{
		cols[0][i] = _ids[i-1]._Node_id;
		cols[i][0] = _ids[i-1]._Node_id;

	}

	for(int i =1;i<Row_Size;i++)
		for(int j=i;j<Row_Size;j++)
		{
			cols[i][j] = edgeExists(cols[0][i],cols[j][0]);	
			cols[j][i] = cols[i][j];	
		}

	return(cols);
}


				//####### Yobanie 2 chesa no4i   :(    ######



//=============================================================================
/* Prints a BFS traversal of the graph  *
   Get source vertex id
*  Returns nothing .                    */
template  <class T>
void Graph<T>::printBFS(int sourceId) const
{
	queue<int> myQueue;									// queue structure
	const int Vertex_Size = _ids.size();				// number of vertexes

	// Define exac position at vector of vertexes ids (vector: ids)
	const int vecSourceId = getVectorPos(sourceId) - 1;	

	// miror to ids ctructur - color structure (enum)
	VertexState *state = new VertexState[Vertex_Size];	

	for(int i = 0; i < Vertex_Size; i++)				// loop all vertexes
		state[i] = White;								// paint them wight
	
	state[vecSourceId] = Gray;			// paint the source vertex to gray

	myQueue.push(vecSourceId);			// push source vertex to queue

	while(myQueue.size())				// loop as long as queue is not empty
	{
		int vertex = myQueue.front();	// define the next vertex at the queue
		myQueue.pop();					// pop the next vertex at the queue

		if(vertex != vecSourceId)		// comma corection
			cout << ",";

		// Print the next discovered vertex id and his data to the STD-OUT
		cout << "|(" << _ids[vertex]._Node_id << "): " << _db[vertex]  << " |";

		// Loop all the neighbors of the curent vertex (that was dequeued)
		for(unsigned int i = 0; i < _ids[vertex]._neighbors.size(); i++)
		{
			// Define exac position at vector of neighbor vertexes ids
			int neighbor = getVectorPos(_ids[vertex]._neighbors[i]) - 1;

			if(state[neighbor] == White)// if vertex not discovered allredy:
			{
				state[neighbor] = Gray; // paint that neighbor vertex to gray
				myQueue.push(neighbor); // push that neighbor vertex to queue
			}
		}
		state[vertex] = Black;	// for extantion of the real algorithm BFS
	}
	delete [] state;			// free memory of color structure (enum)
	cout << "\n";
}

//=============================================================================
/* Prints a DFS traversal of the graph  *
   Get source vertex id
*  Returns nothing .                    */
template  <class T>
void Graph<T>::printDFS(int sourceId) const
{
	const int Vertex_Size = _ids.size();				// number of vertexes

	// miror to ids ctructur - color structure (enum)
	VertexState *state = new VertexState[Vertex_Size];

	for(int i = 0; i < Vertex_Size; i++)				// loop all vertexes
		state[i] = White;								// paint them wight

	// Activate the recursive DFS from source vertex
	runDFS(getVectorPos(sourceId) - 1, state);			
	delete [] state;	// free memory of color structure (enum)

	cout << "\n";
}

//=============================================================================
/* Recursiv "engen" of  DFS algorithem  *
   Get next source vertex and vertexes color ctructur 
*  Returns nothing .                    */
template  <class T>
void Graph<T>::runDFS(int u, VertexState state[]) const
{
	state[u] = Gray;					// paint the source vertex "u" to gray

	// Print the next discovered vertex id and his data to the STD-OUT
	cout << "|(" << _ids[u]._Node_id << "): " << _db[u]  << " |";

	const int Vertex_Size = _ids.size();	// number of vertexes

	for(int v = 0; v < Vertex_Size; v++)	// loop all vertexes
	{
		// If there is an age between "u" and "v" vertexes:
		if(edgeExists(_ids[u]._Node_id, _ids[v]._Node_id) && state[v] == White)
		{
			cout << ",";					// comma corection
			runDFS(v, state);				// call recursiv with current vertx
		}
	}
	state[u] = Black;	// for extantion of the real algorithm DFS
}





//###########     TODO      ##############


//template  <class T>
//int Graph<T>::initElementaryGraphAlgorithm(int vertexId)
//{
//	const int Vertex_Size = _ids.size();				// number of vertexes
//
//	// miror to ids ctructur - color structure (enum)
//	//state = new VertexState[Vertex_Size];
//
//	//for(int i = 0; i < Vertex_Size; i++)				// loop all vertexes
//	//	state[i] = White;
//	return(Vertex_Size);
//}

//=============================================================================
/* Deataches a vertex from its neighbours    *
*  Returns false if vertex does not exists.  */
template  <class T>
bool Graph<T>::detachVertex(int vertexId)
{
	const int Uniq_Pos = getVectorPos(vertexId);

	if(Uniq_Pos)
	{
		DeleteAll_Neighbors(Uniq_Pos-1);
		return(true);
	}
	return(false);
}
//=============================================================================
//=============================================================================
//=============================================================================



//####################################################################
//##                         BUCK UP                                ##
//##================================================================##
//####################################################################







//void Graph::DFS() {
//      VertexState *state = new VertexState[vertexCount];
//      for (int i = 0; i < vertexCount; i++)
//            state[i] = White;
//      runDFS(0, state);
//      delete [] state;
//}
// 
//void Graph::runDFS(int u, VertexState state[]) {
//      state[u] = Gray;
//      for (int v = 0; v < vertexCount; v++)
//            if (isEdge(u, v) && state[v] == White)
//                  runDFS(v, state);
//      state[u] = Black;
//}





	//const int Vertex_Size = _ids.size();

	//for(int i=0;i<Vertex_Size;i++)
	//{
		

		//const int Vertex_Size_Bo = _ids[i]._neighbors.size(); ;

		//cout << "[" << _ids[i]._Node_id << "]";

		//if(Vertex_Size_Bo)
		//	cout << " - " << _db[i] << " \t-\tHave :\n\t";
		//else
		//	cout << "\t\t*******************************************************\n";

		//for(int j=0;j<Vertex_Size_Bo;j++)
		//{
		//	cout << " ;ID:"<<_ids[i]._neighbors[j];
		//}

		//cout << "\n";
	//}
//}

//
//
//
////=============================================================================
///* Prints a DFS traversal of the graph  *
//*  Returns nothing .                    */
//template  <class T>
//void Graph<T>::printDFS(int sourceId) const
//{
//
//	const int Vertex_Size = _ids.size();
//
//	for(int i=0;i<Vertex_Size;i++)
//	{
//		
//
//		const int Vertex_Size_Bo = _ids[i]._neighbors.size(); ;
//
//		cout << "[" << _ids[i]._Node_id << "]";
//
//		if(Vertex_Size_Bo)
//			cout << " - " << _db[i] << " \t-\tHave :\n\t";
//		else
//			cout << "\t\t*******************************************************\n";
//
//		for(int j=0;j<Vertex_Size_Bo;j++)
//		{
//			cout << " ;ID:"<<_ids[i]._neighbors[j];
//		}
//
//		cout << "\n";
//	}
//}
//


////=============================================================================
///* Prints a BFS traversal of the graph  *
//*  Returns nothing .                    */
//template  <class T>
//void Graph<T>::printBFS(int sourceId) const
//{
//	int					*_colors ;					//	Data Base of colors
//	const int NodesSize = countNodes();				//	Number of Vertex
//	_colors				= new int[NodesSize];		//	Create colors
//	vector<int>			buffer;						//	FIFO
//	int **matrix		= getMatrixRepresentation();//	DataBase of edges
//	const int Uniq_Pos	= getVectorPos(sourceId);	//	Source Vertex place
//
//	memset(_colors,0,NodesSize*sizeof(int));					//	Set colors for edges
//	
//	cout << "Looking for ID: " << sourceId << " Vertex\n";	//	NAHUY STERET
//
//	buffer.push_back(Uniq_Pos-1);							
//	_colors[Uniq_Pos-1] = 1;
//	const T* data = NULL;
//
//	while(buffer.size())
//	{
//		int vertex = buffer[0];
//		//cout << "Vetex neighbors size: " << _ids[vertex]._neighbors.size() << " of vertex num:Pos: " << vertex << "\n";
//
//
//		cout << "|(" << _ids[vertex]._Node_id << "): " << _db[vertex]  << " |";
//		for(int i = 1; i<NodesSize+1;i++)
//		{
//		//	//	I tut ne pomnyu
//			//cout << i << " " << vertex << "\t";
//			//cout << "Color: " << _colors[i-1] << "\t";
//			//cout << "Matrix value : " << matrix[vertex][i] << "\n";
//			if(matrix[vertex+1][i] && _colors[i-1]==0)
//			{
//		//		//	Cheto ya nepomnyu chto kuda i kak
//				//if(_colors[i-1]==1)
//				//cout << "Vertex:" << vertex+1 << ":" << i << " and pos " << i-2 <<  "\n";
//				buffer.push_back(i);
//				_colors[i-1] = 1;
//				cout << ",(" << matrix[0][i] << "): " << _db[i]  << " |";
//				//cout << _db[vertex] << ":[" << i-1 << "]" << _db[i-1] << " ";
//			}
//		}
//		cout << "\n";
//		_colors[vertex] = 2;
//		buffer.erase(buffer.begin()+0);
//	}
//
//	//	Clean Used memory in matrix
//	for(int i =0;i<NodesSize+1;i++)
//		delete [] matrix[i];
//
//	//	clear color memery used
//	delete _colors;
//}

////=============================================================================
///* Prints a BFS traversal of the graph  *
//*  Returns nothing .                    */
//template  <class T>
//void Graph<T>::printBFS(int sourceId) const
//{
//	queue<int> myQueue;									// queue structure
//	const int Vertex_Size = _ids.size();				// number of vertexes
//
//	// Define exac position at vector of vertexes ids (vector: ids)
//	const int vecSourceId = getVectorPos(sourceId) - 1;	
//
//	// miror to ids ctructur - color structure (enum)
//	VertexState *state = new VertexState[Vertex_Size];	
//
//	for(int i = 0; i < Vertex_Size; i++)				// loop all vertexes
//		state[i] = White;								// paint them wight
//	
//	state[vecSourceId] = Gray;			// paint the source vertex to gray
//
//	myQueue.push(vecSourceId);			// push source vertex to queue
//
//	while(myQueue.size())				// loop as long as queue is not empty
//	{
//		int vertex = myQueue.front();	// define the next vertex at the queue
//		myQueue.pop();					// pop the next vertex at the queue
//
//		if(vertex != vecSourceId)		// comma corection
//			cout << ",";
//
//		// Print the next discovered vertex id and his data to the STD-OUT
//		cout << "|(" << _ids[vertex]._Node_id << "): " << _db[vertex]  << " |";
//
//		// Loop all the neighbors of the curent vertex (that was dequeued)
//		for(unsigned int i = 0; i < _ids[vertex]._neighbors.size(); i++)
//		{
//			// Define exac position at vector of neighbor vertexes ids
//			int neighbor = getVectorPos(_ids[vertex]._neighbors[i]) - 1;
//
//			if(state[neighbor] == White)// if vertex not discovered allredy:
//			{
//				state[neighbor] = Gray; // paint that neighbor vertex to gray
//				myQueue.push(neighbor); // push that neighbor vertex to queue
//			}
//		}
//		state[vertex] = Black;	// for extantion of the real algorithm BFS
//	}
//	delete [] state;			// free memory of color structure (enum)
//	cout << "\n";
//}
//
////=============================================================================
///* Prints a DFS traversal of the graph  *
//*  Returns nothing .                    */
//template  <class T>
//void Graph<T>::printDFS(int sourceId) const
//{
//	const int Vertex_Size = _ids.size();				// number of vertexes
//
//	// miror to ids ctructur - color structure (enum)
//	VertexState *state = new VertexState[Vertex_Size];
//
//	for(int i = 0; i < Vertex_Size; i++)				// loop all vertexes
//		state[i] = White;								// 
//
//	runDFS(getVectorPos(sourceId) - 1, state);
//	delete [] state;
//
//	cout << "\n";
//}
//
////=============================================================================
//template  <class T>
//void Graph<T>::runDFS(int u, VertexState state[]) const
//{
//	state[u] = Gray;
//
//	cout << "|(" << _ids[u]._Node_id << "): " << _db[u]  << " |";
//
//	const int Vertex_Size = _ids.size();
//
//	for(int v = 0; v < Vertex_Size; v++)
//	{
//		if(edgeExists(_ids[u]._Node_id, _ids[v]._Node_id) && state[v] == White)
//		{
//			cout << ",";
//			runDFS(v, state);
//		}
//	}
//	state[u] = Black;	// for extantion of the real algorithm DFS
//}
