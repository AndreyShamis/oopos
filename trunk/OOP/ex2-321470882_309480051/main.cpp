//
//  @ Project : Graph
//  @ File Name : main.cpp
//  @ Date : 13/3/2011
//  @ Authors : Ilia Gaysinski and Andrey Shamis
//	@ Description : 
//

#include <iostream>
#include "macros.h"
#include "HadassahGraph.h"
#include "Graph.h"

using namespace std;


//=============================================================================
//	Main function
int main()
{
	//typedef Graph<struct BFS_node> BFSgraph();
	Graph<int> BFSgraph;
	Graph<float> BFSgraph2;
	
	//BFS_node kodkod;
	//kodkod._value = 0.01;

	int data = 10;
	float we = 0.1f;
	//BFSgraph.addVertex(data);
	BFSgraph.addVertex(data);
	BFSgraph2.addVertex(we);
	cout << "Was up UFO\n";
	
	return(0);
}