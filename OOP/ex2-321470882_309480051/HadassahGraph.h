//
//  @ Project : Graph
//  @ File Name : HadassahGraph.h
//  @ Date : 13/3/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : 
//

#pragma once
#include "macros.h"

//Hadassah EX2 Graph interface
template <class T>
class HadassahGraph{

public:
	
	/* Adds a vertex to the graph *
	 * Returns unique vertex id   */
	virtual int addVertex(const T data)=0;

	/* Removes a vertex with id= vertexId       *
	*  Returns false if vertex does not exists  */
	virtual bool removeVertex(int vertexId)=0;
  
	/* Adds an edge between vertexId1 and vertexId2          *
	*  Returns false if one of the vertices does not exists  */
	virtual bool addEdge(int vertexId1, int vertexId2)=0;

	/* Removes an edge between vertexId1 and vertexId2       *
	*  Returns false if one of the vertices does not exists  */
	virtual bool removeEdge(int vertexId1, int vertexId2)=0;

	/* Check if an edge exists in the graph                                      *
	*  Returns false if one of the vertices does not exists or there is no edge  */
	virtual bool edgeExists(int vertexId1, int vertexId2) const=0;

	/* Get the data of a vertex in the graph                        *
	*  Returns the data of type T, NULL if vertex does not exists.  */
	virtual const T* const getData(int vertexId)=0;

	/* Count graph edges                         *
	*  Returns the number of edges in the graph  */
	virtual int countEdges() const=0;

	/* Count graph vertices                         *
	*  Returns the number of vertices in the graph  */
	virtual int countNodes() const=0;

	/* Get the matrix representation of the graph   *
	*  Returns an int matrix .                      */
	virtual int** getMatrixRepresentation() const=0;

	/* Prints a BFS traversal of the graph  *
	*  Returns nothing .                    */
	virtual void printBFS(int sourceId) const=0;

	/* Prints a DFS traversal of the graph  *
	*  Returns nothing .                    */
	virtual void printDFS(int sourceId) const=0;

	/* Deataches a vertex from its neighbours    *
	*  Returns false if vertex does not exists.  */
	virtual bool detachVertex(int vertexId)=0; 


	};