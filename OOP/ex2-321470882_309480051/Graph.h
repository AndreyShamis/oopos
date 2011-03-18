#pragma once
#include <vector>
#include "macros.h"
#include "hadassahgraph.h"
using namespace std;


#define MAX_DEFAULT_SIZE_CAN_BE 9999999999;

template  <class T>
class Graph: public HadassahGraph<T>
{
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
	bool addEdge(int vertexId1, int vertexId2);

	/* Removes an edge between vertexId1 and vertexId2       *
	*  Returns false if one of the vertices does not exists  */
	bool removeEdge(int vertexId1, int vertexId2);

	/* Check if an edge exists in the graph                                      *
	*  Returns false if one of the vertices does not exists or there is no edge  */
	bool edgeExists(int vertexId1, int vertexId2) const;

	/* Get the data of a vertex in the graph                        *
	*  Returns the data of type T, NULL if vertex does not exists.  */
	const T* const getData(int vertexId);

	/* Count graph edges                         *
	*  Returns the number of edges in the graph  */
	int countEdges() const;

	/* Count graph vertices                         *
	*  Returns the number of vertices in the graph  */
	int countNodes() const;

	/* Get the matrix representation of the graph   *
	*  Returns an int matrix .                      */
	int** getMatrixRepresentation() const;

	/* Prints a BFS traversal of the graph  *
	*  Returns nothing .                    */
	void printBFS(int sourceId) const;

	/* Prints a DFS traversal of the graph  *
	*  Returns nothing .                    */
	void printDFS(int sourceId) const;

	/* Deataches a vertex from its neighbours    *
	*  Returns false if vertex does not exists.  */
	bool detachVertex(int vertexId); 

private:

	vector <T *> _id_of_node;

	unsigned int _max_size_can_be;

	unsigned int _counter;
	//vector<int> _ol;
};
