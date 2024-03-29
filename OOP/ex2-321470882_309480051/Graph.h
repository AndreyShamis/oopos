//
//  @ Project : Graph
//  @ File Name : main.cpp
//  @ Date : 13/3/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description :		Class of Graph
//

//	Class provide graph. 
#pragma once
#include <vector>
#include <queue>
#include "macros.h"
#include "hadassahgraph.h"
using namespace std;


//#define MAX_DEFAULT_SIZE_CAN_BE 99999999			//	max size of vertexs in graph

template <class T> 
class Graph : public HadassahGraph<T>
{
	enum VertexState { White, Gray, Black };

	//	Struct for representetion neighbors
	//	and id of vertex
	struct SomeNode
	{
		int				_Node_id;	//	id
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

	vector <T>			_db;				//	Data base for data
	vector <SomeNode>	_ids;				//	DB representation
	unsigned int		_insert_id;			//	Insert ID

	//	Furures	variables
	unsigned int		_max_size_can_be;	//	Max size of graph vertexs
	bool				_Graph_ValuesUniqe;	//	Unique values in graph
	
	//	Helps functions
	int		getVectorPos(const int Uniq_ID) const;
	void	DeleteAll_Neighbors(const int VertexAxactPosition);
	void	DeleteNeighborByID(const int SelfID,const int NeighborID);
	bool	HaveEdge(const int SelfID,const int NeighborID)const;
	void	runDFS(int u, VertexState state[]) const;

};

//=============================================================================
//=============================================================================
//=============================================================================
//	Calss constructor
template <class T> 
Graph<T>::Graph()
{
	//	set max size	of vertexs in graph
	//_max_size_can_be	= MAX_DEFAULT_SIZE_CAN_BE;
	
	_insert_id			=	0;		//	reset insert id to start value
	_Graph_ValuesUniqe	=	false;	//	set default graph be not unique
}  

//=============================================================================
//	Function wich can find some vertex by him value. 
//	It is advisable to use this feature only if the graph is set to 
//	unique values​​. Anyway the decision to use this feature being 
//	touted developer.
//	Function returns a value ID for vertex in the first it finds 
//	that contains the specified value.
template <class T> 
int	Graph<T>::getIDbyValue(const T data)const
{
	const int VertexCount = countNodes();	//	get size of vector 

	for(int i=0;i<VertexCount;i++)			//	Strat looking and compare
	{										//	data vlues
		if(_db[i] == data)					//	If found equalent
		{
			return(_ids[i]._Node_id);		//	return ID
		}
	}

	return(0);								//	if not found return 0
}

//=============================================================================
//	The function is used like futures in case if you need create unique 
//	values in some vertex of graph
template <class T> 
void Graph<T>::setUniq_values(const bool newValue)
{
	//	First case work only if no found any vertex in graph
	//	and second case work only if the graph actualy is unique and have only unique value
	//	and you want to transform the graph to not unique value vertex
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
	//	Used for unique values graph(see readme).
	if(_Graph_ValuesUniqe && getIDbyValue(data))
		return(0);

	//	Increase insert ID
	_insert_id++;
	_db.push_back(data);				//	push data into vector

	SomeNode newNode;					//	struct of DB structure
	newNode._Node_id = _insert_id;		//	The ID of new vertex
	_ids.push_back(newNode);			//	push new DB structure into vector
	
	return(_insert_id);					//	return ID of new vertex
}

//=============================================================================
//	Get exact position of vertex in vector by ID
//	The retrned value must be
//		value-1
//	its give options for check if retuned value = 0 thats mean
//	the verex with this id not found and array position 0 cab be 
//	found in array
template <class T> 
int Graph<T>::getVectorPos(const int Uniq_ID) const
{
		
	const int Vertex_Size = _ids.size();	//	Get size of Vertexs	

	//	Check each struct for id 
	for(int i=0;i<Vertex_Size;i++)
	{
		//	If found thats value
		//	increase by 1 the value(see function description)
		if(_ids[i]._Node_id == Uniq_ID)
			return(i+1);					
	}

	return(0);	//	return 0 becouse not found(see function description)
}

//=============================================================================
//	Function wich getig actualy position of main vertex and ID of second vertex
//	and return true if they have edge
template <class T> 
bool Graph<T>::HaveEdge(const int SelfID,const int NeighborID)const
{
		
	//	Get actual size of vertex neighbors
	const int Neighbors_Size = _ids[SelfID]._neighbors.size();

	//	for each neighbor in vector
	for(int i=0;i<Neighbors_Size;i++)
	{
		//	check if main vertex have neighbor with NeighborID
		if(_ids[SelfID]._neighbors[i] == NeighborID)
			return(true);	//	if have return true
	}

	return(false);			//	not have
}

//=============================================================================
//	Function wich delete all neighbors from vertex and from his neighbors
//	himself
template <class T> 
void Graph<T>::DeleteAll_Neighbors(const int VertexAxactPosition)
{
	//	Get actual size of vertex neighbors
	const int Neighbors_Size = _ids[VertexAxactPosition]._neighbors.size();
	
	//	For each neighbors
	for(int i = 0; i<Neighbors_Size;i++)
	{
		//	if the vertex is not himself delete him from his neighbor
		if(_ids[VertexAxactPosition]._neighbors[i] != _ids[VertexAxactPosition]._Node_id)
			DeleteNeighborByID(VertexAxactPosition,_ids[VertexAxactPosition]._neighbors[i]);
	}

	//	clear all values in vertex neighbors 
	_ids[VertexAxactPosition]._neighbors.clear();

}
//=============================================================================
//	function for delete him(SelfID actualy postion of vertex in array) from 
//	his neighbor which have ID delete him from his neighbor
template <class T> 
void Graph<T>::DeleteNeighborByID(const int SelfID,const int NeighborID)
{
	//	calculate actualy postion of neighbor in db structure
	const int Npos = getVectorPos(NeighborID);

	//	if found neighbor with this NeighborID  
	if(Npos)
	{
		//	Looking in vector of neighbor for main vertex
		for(int j=0;j < (int)_ids[Npos-1]._neighbors.size();j++)
		{
			//	if found delete him from there
			if(_ids[Npos-1]._neighbors[j] == _ids[SelfID]._Node_id)
			{
				_ids[Npos-1]._neighbors.erase(_ids[Npos-1]._neighbors.begin()+j);
				j--;		//	not used but if break be deleted must work
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
	//	calculate actualy postion of vertex in db structure
	const int Uniq_Pos = getVectorPos(vertexId);

	if(Uniq_Pos)							//	If actual postion not 0
	{
		DeleteAll_Neighbors(Uniq_Pos-1);	//	Delete all edges
		_db.erase(_db.begin()+Uniq_Pos-1);	//	clear data from vector
		_ids.erase(_ids.begin()+Uniq_Pos-1);//	clear struture from vector
		return(true);						//	return true
	}

	return(false);							//	not found
}

//=============================================================================
/* Adds an edge between vertexId1 and vertexId2          *
*  Returns false if one of the vertices does not exists  */
// TODO check if have edge need to do
template <class T>
bool Graph<T>::addEdge(int vertexId1, int vertexId2)
{
	const int First_Pos		=	getVectorPos(vertexId1);//	get actual position
	const int Second_Pos	=	getVectorPos(vertexId2);//	get actual position
	
	//	in case if two vertex have diferent id and they founded
	if(First_Pos && Second_Pos && First_Pos != Second_Pos 
		&& !HaveEdge(First_Pos-1,vertexId2))
	{
		_ids[First_Pos-1]._neighbors.push_back(vertexId2);//	add edge
		_ids[Second_Pos-1]._neighbors.push_back(vertexId1);//	add edge
		return(true);
	}
	else if(First_Pos && First_Pos == Second_Pos //	second case
		&& !HaveEdge(First_Pos-1,vertexId1))
	{	//	in wich two vertexs is same vertex
		_ids[First_Pos-1]._neighbors.push_back(vertexId1);//	add edge
		return(true);
	}

	return(false);		//	if not found any vertex
}

//=============================================================================
/* Removes an edge between vertexId1 and vertexId2       *
*  Returns false if one of the vertices does not exists  */
template <class T>
bool Graph<T>::removeEdge(int vertexId1, int vertexId2)
{
	const int First_Pos		=	getVectorPos(vertexId1);//	get actual position
	const int Second_Pos	=	getVectorPos(vertexId2);//	get actual position
	
	//	in case if two vertex have diferent id and they founded
	if(First_Pos && Second_Pos && First_Pos != Second_Pos)
	{
		DeleteNeighborByID(First_Pos-1,vertexId2);	//	delete neighbor
		DeleteNeighborByID(Second_Pos-1,vertexId1);	//	delete neighbor
		return(true);
	}
	else if(First_Pos && Second_Pos && First_Pos == Second_Pos)//	second case
	{	//	in wich two vertexs is same vertex
		DeleteNeighborByID(First_Pos-1,vertexId1);	//	delete neighbor
		return(true);
	}

	return(false);		//	if not found any vertex
}

//=============================================================================
/* Check if an edge exists in the graph                                      *
*  Returns false if one of the vertices does not exists or there is no edge  */
template <class T>
bool Graph<T>::edgeExists(int vertexId1, int vertexId2) const
{
	const int First_Pos		=	getVectorPos(vertexId1);//	get actual position
	const int Second_Pos	=	getVectorPos(vertexId2);//	get actual position

	//	in case if two vertex have diferent id and they founded
	if(First_Pos && Second_Pos && First_Pos != Second_Pos)
	{
		//	if have edge
		if(HaveEdge(First_Pos-1,vertexId2) &&	HaveEdge(Second_Pos-1,vertexId1))
			return(true);
	}
	else if(First_Pos && First_Pos == Second_Pos)//	second case
	{	//	in wich two vertexs is same vertex
		//	if have edge
		if(HaveEdge(First_Pos-1,vertexId1))
			return(true);
	}

	return(false);		///	if not found any vertex
}

//=============================================================================
/* Get the data of a vertex in the graph                        *
*  Returns the data of type T, NULL if vertex does not exists.  */
template <class T>
const T* const Graph<T>::getData(int vertexId)
{
	//	calculate actualy postion of vertex in db structure
	const int Ver_Pos		=	getVectorPos(vertexId);
	T			*s			=	NULL;		//	return value

	if(Ver_Pos)								//	if found vertex with this ID
		s = &_db[Ver_Pos-1];				//	set pointer

	return(s);								//	return pointer
}

//=============================================================================
/* Count graph edges                         *
*  Returns the number of edges in the graph  */
template <class T>
int Graph<T>::countEdges() const
{
	const int Vertex_Size = _ids.size();	//	get vectyor size
	int return_value = 0;					//	return value

	//	Start calculate the edges
	for(int i =0;i<Vertex_Size;i++)
		for(int j=i;j<Vertex_Size;j++)
		{
			//	for each vertex wich have some X vector postion
			//	and each vertex wich have more than X-1 postion
			if(edgeExists(_ids[i]._Node_id,_ids[j]._Node_id))
				return_value++;				//	increase counter
		}

	return(return_value);					//	return value
}

//=============================================================================
/* Count graph vertices                         *
*  Returns the number of vertices in the graph  */
template <class T>
int Graph<T>::countNodes() const
{
	return((int)_db.size());				//	return size of vertex
}

//=============================================================================
/* Get the matrix representation of the graph   *
*  Returns an int matrix .                      */
template <class T>
int** Graph<T>::getMatrixRepresentation() const
{

	const int Row_Size = 1+_db.size();	//	size of table
	int **cols=NULL;					//	return value

	cols = new(std::nothrow) int*[Row_Size];	//	allocate memory

	if(cols != NULL)							//	check allocating
	{	
		for(int i=0;i<Row_Size;i++)
		{
			cols[i] = new (std::nothrow) int[Row_Size];	//	allocate memory
			if(cols[i] == NULL)
			{	//	error print and exit
				cerr << "Can`t allocate memory\n";
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{	//	error print and exit
		cerr << "Can`t allocate memory\n";
		exit(EXIT_FAILURE);
	}

	cols[0][0] = Row_Size -1;					//	print into matrix vertex count

	//	fill first row and first column whith ID`s of vertex
	for(int i =1;i<Row_Size;i++)
	{
		cols[0][i] = _ids[i-1]._Node_id;		//	row
		cols[i][0] = _ids[i-1]._Node_id;		//	column

	}

	//	fill the matrix with values if two vertexs have edge
	for(int i =1;i<Row_Size;i++)
		for(int j=i;j<Row_Size;j++)
		{
			cols[i][j] = edgeExists(cols[0][i],cols[j][0]);	
			cols[j][i] = cols[i][j];	
		}

	return(cols);								//	return matrix
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

//=============================================================================
/* Deataches a vertex from its neighbours    *
*  Returns false if vertex does not exists.  */
template  <class T>
bool Graph<T>::detachVertex(int vertexId)
{
	const int Uniq_Pos = getVectorPos(vertexId);	//	get actual position

	if(Uniq_Pos)									//	if found
	{
		DeleteAll_Neighbors(Uniq_Pos-1);			//	clear all neihgbors
		return(true);								//	return found
	}
	return(false);									//	return false
}
//=============================================================================
//=============================================================================
//=============================================================================