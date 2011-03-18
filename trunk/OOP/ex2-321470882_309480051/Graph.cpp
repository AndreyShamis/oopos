#include "Graph.h"
template  <class T>
Graph<T>::Graph()
{
	_max_size_can_be	= MAX_DEFAULT_SIZE_CAN_BE;
	_counter			=	0;
}


/* Adds a vertex to the graph *
 * Returns unique vertex id   */
template  <class T>
int Graph<T>::addVertex(const T data)
{
	//_id_of_node.push_back(<BFS_node>data);
	_counter++;
	return(1);
}

/* Removes a vertex with id= vertexId       *
*  Returns false if vertex does not exists  */
template  <class T>
bool Graph<T>::removeVertex(int vertexId)
{
	return(1);
}

/* Adds an edge between vertexId1 and vertexId2          *
*  Returns false if one of the vertices does not exists  */
template  <class T>
bool Graph<T>::addEdge(int vertexId1, int vertexId2)
{
	return(1);
}

/* Removes an edge between vertexId1 and vertexId2       *
*  Returns false if one of the vertices does not exists  */
template  <class T>
bool Graph<T>::removeEdge(int vertexId1, int vertexId2)
{
	return(1);
}

/* Check if an edge exists in the graph                                      *
*  Returns false if one of the vertices does not exists or there is no edge  */
template  <class T>
bool Graph<T>::edgeExists(int vertexId1, int vertexId2) const
{
	return(1);
}

/* Get the data of a vertex in the graph                        *
*  Returns the data of type T, NULL if vertex does not exists.  */
template  <class T>
const T* const Graph<T>::getData(int vertexId)
{
	return(1);
}

/* Count graph edges                         *
*  Returns the number of edges in the graph  */
template  <class T>
int Graph<T>::countEdges() const
{
	return(1);
}

/* Count graph vertices                         *
*  Returns the number of vertices in the graph  */
template  <class T>
int Graph<T>::countNodes() const
{
	return(1);
}

/* Get the matrix representation of the graph   *
*  Returns an int matrix .                      */
template  <class T>
int** Graph<T>::getMatrixRepresentation() const
{
	int **lol;
	return(lol);
}

/* Prints a BFS traversal of the graph  *
*  Returns nothing .                    */
template  <class T>
void Graph<T>::printBFS(int sourceId) const
{

	;
}

/* Prints a DFS traversal of the graph  *
*  Returns nothing .                    */
template  <class T>
void Graph<T>::printDFS(int sourceId) const
{
	;
}

/* Deataches a vertex from its neighbours    *
*  Returns false if vertex does not exists.  */
template  <class T>
bool Graph<T>::detachVertex(int vertexId)
{
	return(1);
}