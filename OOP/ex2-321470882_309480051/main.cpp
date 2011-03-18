//
//  @ Project : Graph
//  @ File Name : main.cpp
//  @ Date : 13/3/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : 
//

#include <iostream>

#include "Graph.h"
#include "macros.h"

using namespace std;

template  <class T>
//=============================================================================
//	Main function
int main()
{
	//typedef Graph<struct BFS_node>;
	Graph<struct BFS_node> BFSgraph;
	BFS_node kodkod;
	kodkod._value = 0.01;

	BFSgraph.addVertex();
	cout << "Was up UFO\n";
	
	return(0);
}