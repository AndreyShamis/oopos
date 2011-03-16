#include "Grpah.h"

Grpah::Grpah()
{
	;
}

Grpah::~Grpah()
{
	;
}

/* Adds a vertex to the graph *
 * Returns unique vertex id   */
int Grpah::addVertex(const T data)
{
	return(1);
}

/* Removes a vertex with id= vertexId       *
*  Returns false if vertex does not exists  */
bool Grpah::removeVertex(int vertexId)
{
	return(1);
}

/* Adds an edge between vertexId1 and vertexId2          *
*  Returns false if one of the vertices does not exists  */
bool Grpah::addEdge(int vertexId1, int vertexId2)
{
	return(1);
}

/* Removes an edge between vertexId1 and vertexId2       *
*  Returns false if one of the vertices does not exists  */
bool Grpah::removeEdge(int vertexId1, int vertexId2)
{
	return(1);
}

/* Check if an edge exists in the graph                                      *
*  Returns false if one of the vertices does not exists or there is no edge  */
bool Grpah::edgeExists(int vertexId1, int vertexId2) const
{
	return(1);
}

/* Get the data of a vertex in the graph                        *
*  Returns the data of type T, NULL if vertex does not exists.  */
const T* const Grpah::getData(int vertexId)
{
	return(1);
}

/* Count graph edges                         *
*  Returns the number of edges in the graph  */
int Grpah::countEdges() const
{
	return(1);
}

/* Count graph vertices                         *
*  Returns the number of vertices in the graph  */
int Grpah::countNodes() const
{
	return(1);
}

/* Get the matrix representation of the graph   *
*  Returns an int matrix .                      */
int** Grpah::getMatrixRepresentation() const
{
	return(1);
}

/* Prints a BFS traversal of the graph  *
*  Returns nothing .                    */
void Grpah::printBFS(int sourceId) const;

/* Prints a DFS traversal of the graph  *
*  Returns nothing .                    */
void Grpah::printDFS(int sourceId) const
{
	return(1);
}

/* Deataches a vertex from its neighbours    *
*  Returns false if vertex does not exists.  */
bool Grpah::detachVertex(int vertexId)
{
	return(1);
}