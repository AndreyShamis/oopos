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
		int	_Node_id;
		vector <int> _neighbors;
	};
public:
	Graph();
	/* Adds a vertex to the graph *
	 * Returns unique vertex id   */
	int addVertex(const T data);

	/* Removes a vertex with id= vertexId       *
	*  Returns false if vertex does not exists  */
	bool removeVertex(int vertexId);

	/* Adds an edge between vertexId1 and vertexId2          *
	*  Returns false if one of the vertices does not exists  */
	virtual bool addEdge(int vertexId1, int vertexId2);

	/* Removes an edge between vertexId1 and vertexId2       *
	*  Returns false if one of the vertices does not exists  */
	virtual bool removeEdge(int vertexId1, int vertexId2);

	/* Check if an edge exists in the graph                                      *
	*  Returns false if one of the vertices does not exists or there is no edge  */
	virtual bool edgeExists(int vertexId1, int vertexId2) const;

	/* Get the data of a vertex in the graph                        *
	*  Returns the data of type T, NULL if vertex does not exists.  */
	virtual const T* const getData(int vertexId);

	/* Count graph edges                         *
	*  Returns the number of edges in the graph  */
	virtual int countEdges() const;

	/* Count graph vertices                         *
	*  Returns the number of vertices in the graph  */
	virtual int countNodes() const;

	/* Get the matrix representation of the graph   *
	*  Returns an int matrix .                      */
	virtual int** getMatrixRepresentation() const;

	/* Prints a BFS traversal of the graph  *
	*  Returns nothing .                    */
	virtual void printBFS(int sourceId) const;

	/* Prints a DFS traversal of the graph  *
	*  Returns nothing .                    */
	virtual void printDFS(int sourceId) const;

	/* Deataches a vertex from its neighbours    *
	*  Returns false if vertex does not exists.  */
	virtual bool detachVertex(int vertexId); 

private:

	vector <T>		_id_of_node;
	vector <SomeNode>	_ids;
	//T _id_of_node;
	unsigned int	_max_size_can_be;

	unsigned int	_counter;
	
	int getVectorPos(const int Uniq_ID) const;
	void DeleteAll_Neighbors(const int VertexAxactPosition);
	void DeleteNeighborByID(const int SelfID,const int NeighborID);
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
	{
		if(_ids[i]._Node_id == Uniq_ID)
		{
			return(i+1);
		}
	}	

	return(0);
}


//=============================================================================
template <class T> 
void Graph<T>::DeleteAll_Neighbors(const int VertexAxactPosition)
{
	const int Neighbors_Size = _ids[VertexAxactPosition]._neighbors.size();

	for(int i = 0; i<Neighbors_Size;i++)
	{
		DeleteNeighborByID(VertexAxactPosition,_ids[VertexAxactPosition]._neighbors[i]);
		
	}
}
//=============================================================================
template <class T> 
void Graph<T>::DeleteNeighborByID(const int SelfID,const int NeighborID)
{

	const int Neighbor = getVectorPos(NeighborID);

	if(Neighbor)
	{
		//cout << "Check neighbor N:"<<Neighbor-1 << "\n";
		//cout << "Which have " << (int)_ids[Neighbor-1]._neighbors.size() << " neighbors\n";
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
	return(1);
}

//=============================================================================
/* Get the data of a vertex in the graph                        *
*  Returns the data of type T, NULL if vertex does not exists.  */
template  <class T>
const T* const Graph<T>::getData(int vertexId)
{
	T *s=NULL;
	return(s);
}

//=============================================================================
/* Count graph edges                         *
*  Returns the number of edges in the graph  */
template  <class T>
int Graph<T>::countEdges() const
{
	return(1);
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

	int **la=NULL;

	return(la);
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
		cout << "[" << _ids[i]._Node_id << "] - " << _id_of_node[i] << "\n";
		cout << "Have :\n\t";

		const int Vertex_Size_Bo = _ids[i]._neighbors.size(); ;

		for(int j=0;j<Vertex_Size_Bo;j++)
		{
			cout << "ID:"<<_ids[i]._neighbors[j] << " ;";
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
	;
}

//=============================================================================
/* Deataches a vertex from its neighbours    *
*  Returns false if vertex does not exists.  */
template  <class T>
bool Graph<T>::detachVertex(int vertexId)
{
	return(1);
}
//=============================================================================
//=============================================================================
//=============================================================================