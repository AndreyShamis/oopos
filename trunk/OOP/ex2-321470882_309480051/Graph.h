#pragma once
#include <vector>
#include "macros.h"
#include "hadassahgraph.h"
using namespace std;


#define MAX_DEFAULT_SIZE_CAN_BE 999999

template <class T> 
class Graph : public HadassahGraph<T>
{
	struct SomeNode
	{
		int				_Node_id;
		vector <int>	_neighbors;
	};
public:
	Graph();
	int addVertex(const T data);
	bool removeVertex(int vertexId);
	bool addEdge(int vertexId1, int vertexId2);
	bool removeEdge(int vertexId1, int vertexId2);
	bool edgeExists(int vertexId1, int vertexId2) const;
	const T* const getData(int vertexId);
	int countEdges() const;
	int countNodes() const;
	int** getMatrixRepresentation() const;
	void printBFS(int sourceId) const;
	void printDFS(int sourceId) const;
	bool detachVertex(int vertexId); 

private:

	vector <T>			_id_of_node;
	vector <SomeNode>	_ids;
	unsigned int		_max_size_can_be;
	unsigned int		_counter;
	
	int getVectorPos(const int Uniq_ID) const;
	void DeleteAll_Neighbors(const int VertexAxactPosition);
	void DeleteNeighborByID(const int SelfID,const int NeighborID);
	bool HaveEdge(const int SelfID,const int NeighborID)const;

};

//=============================================================================
//=============================================================================
//=============================================================================

template <class T> 
Graph<T>::Graph()
{
	_max_size_can_be	= MAX_DEFAULT_SIZE_CAN_BE;
	_counter			=	0;
}  
//=============================================================================

/* Adds a vertex to the graph *
 * Returns unique vertex id   */
template <class T> 
int Graph<T>::addVertex(const T data)
{
	_counter++;
	_id_of_node.push_back(data);
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
		if(_ids[i]._Node_id == Uniq_ID)
			return(i+1);

	return(0);
}

//=============================================================================
template <class T> 
bool Graph<T>::HaveEdge(const int SelfID,const int NeighborID)const
{
		
	const int Neighbors_Size = _ids[SelfID]._neighbors.size();

	for(int i=0;i<Neighbors_Size;i++)
		if(_ids[SelfID]._neighbors[i] == NeighborID)
			return(true);

	return(false);
}

//=============================================================================
template <class T> 
void Graph<T>::DeleteAll_Neighbors(const int VertexAxactPosition)
{
	const int Neighbors_Size = _ids[VertexAxactPosition]._neighbors.size();

	for(int i = 0; i<Neighbors_Size;i++)
		DeleteNeighborByID(VertexAxactPosition,_ids[VertexAxactPosition]._neighbors[i]);

}
//=============================================================================
template <class T> 
void Graph<T>::DeleteNeighborByID(const int SelfID,const int NeighborID)
{

	const int Neighbor = getVectorPos(NeighborID);

	if(Neighbor)
		for(int j=0;j < (int)_ids[Neighbor-1]._neighbors.size();j++)
			if(_ids[Neighbor-1]._neighbors[j] == _ids[SelfID]._Node_id)
			{
				_ids[Neighbor-1]._neighbors.erase(_ids[Neighbor-1]._neighbors.begin()+j);
				j--;
				break;
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
		_id_of_node.erase(_id_of_node.begin()+Uniq_Pos-1);
		_ids.erase(_ids.begin()+Uniq_Pos-1);
		return(true);
	}

	return(false);
}

//=============================================================================
/* Adds an edge between vertexId1 and vertexId2          *
*  Returns false if one of the vertices does not exists  */
template  <class T>
bool Graph<T>::addEdge(int vertexId1, int vertexId2)
{
	const int First_Pos		=	getVectorPos(vertexId1);
	const int Second_Pos	=	getVectorPos(vertexId2);
	
	if(First_Pos && Second_Pos && First_Pos != Second_Pos)
	{
		_ids[First_Pos-1]._neighbors.push_back(vertexId2);
		_ids[Second_Pos-1]._neighbors.push_back(vertexId1);
		return(true);
	}
	else if(First_Pos && Second_Pos && First_Pos == Second_Pos)
	{
		_ids[First_Pos-1]._neighbors.push_back(vertexId1);
		return(true);
	}

	return(false);
}

//=============================================================================
/* Removes an edge between vertexId1 and vertexId2       *
*  Returns false if one of the vertices does not exists  */
template  <class T>
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
template  <class T>
bool Graph<T>::edgeExists(int vertexId1, int vertexId2) const
{
	const int First_Pos		=	getVectorPos(vertexId1);
	const int Second_Pos	=	getVectorPos(vertexId2);

	if(First_Pos && Second_Pos && First_Pos != Second_Pos)
		if(HaveEdge(First_Pos-1,vertexId2) &&	HaveEdge(Second_Pos-1,vertexId1))
			return(true);
	else if(First_Pos && Second_Pos && First_Pos == Second_Pos)
		if(HaveEdge(First_Pos-1,vertexId1))
			return(true);


	return(false);
}

//=============================================================================
/* Get the data of a vertex in the graph                        *
*  Returns the data of type T, NULL if vertex does not exists.  */
template  <class T>
const T* const Graph<T>::getData(int vertexId)
{
	const int Ver_Pos		=	getVectorPos(vertexId);
	T			*s			=	NULL;

	if(Ver_Pos)
		s = &_id_of_node[Ver_Pos-1];

	return(s);
}

//=============================================================================
/* Count graph edges                         *
*  Returns the number of edges in the graph  */
template  <class T>
int Graph<T>::countEdges() const
{
	const int Vertex_Size = _ids.size();
	int return_value = 0;

	//	Farej rulez 
	for(int i =0;i<Vertex_Size;i++)
		for(int j=i;j<Vertex_Size;j++)
			if(edgeExists(_ids[i]._Node_id,_ids[j]._Node_id))
				return_value++;

	return(return_value);
}

//=============================================================================
/* Count graph vertices                         *
*  Returns the number of vertices in the graph  */
template  <class T>
int Graph<T>::countNodes() const
{
	const int count = (int)_id_of_node.size();
	return(count);
}

//=============================================================================
/* Get the matrix representation of the graph   *
*  Returns an int matrix .                      */
template  <class T>
int** Graph<T>::getMatrixRepresentation() const
{

	const int Row_Size = 1+_id_of_node.size();
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
		for(int j=1;j<Row_Size;j++)
			cols[i][j] = edgeExists(cols[0][i],cols[j][0]);	

	return(cols);
}

//=============================================================================
/* Prints a BFS traversal of the graph  *
*  Returns nothing .                    */
template  <class T>
void Graph<T>::printBFS(int sourceId) const
{
	const int Vertex_Size = _ids.size();

	for(int i=0;i<Vertex_Size;i++)
	{
		

		const int Vertex_Size_Bo = _ids[i]._neighbors.size(); ;

		cout << "[" << _ids[i]._Node_id << "]";

		if(Vertex_Size_Bo)
			cout << " - " << _id_of_node[i] << " \t-\tHave :\n\t";
		else
			cout << "\t\t*******************************************************\n";

		for(int j=0;j<Vertex_Size_Bo;j++)
		{
			cout << " ;ID:"<<_ids[i]._neighbors[j];
		}

		cout << "\n";
	}
}

//=============================================================================
/* Prints a DFS traversal of the graph  *
*  Returns nothing .                    */
template  <class T>
void Graph<T>::printDFS(int sourceId) const
{
	//int **matrix = getMatrixRepresentation();
	//const int Uniq_Pos = getVectorPos(vertexId);
	;
}

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