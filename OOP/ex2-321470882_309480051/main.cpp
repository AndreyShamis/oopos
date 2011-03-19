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
	int f = BFSgraph.addVertex(data);
	int s = BFSgraph.addVertex(data+2);
	int s1 = BFSgraph.addVertex(data+3);
	int s2 = BFSgraph.addVertex(data+5);
	BFSgraph.addVertex(data+6);
	BFSgraph.addVertex(data+1);
	
	if(BFSgraph.addEdge(f,s))
		cout << "Added\n";
	else
		cout << "Not Added\n";

	if(BFSgraph.addEdge(s1,s1))
		cout << "Added\n";
	else
		cout << "Not Added\n";

	

	BFSgraph.printBFS(data);
	
	if(BFSgraph.removeVertex(s))
		cout << "Deleted\n";
	else
		cout << "Not Deleted\n";

	BFSgraph.printBFS(data);



	int s3 = BFSgraph.addVertex(data+5);
	if(BFSgraph.addEdge(f,s3))
		cout << "Added\n";
	else
		cout << "Not Added\n";

	BFSgraph.printBFS(data);

	if(BFSgraph.removeEdge(f,s3))
		cout << "Added\n";
	else
		cout << "Not Added\n";

	BFSgraph.printBFS(data);
	BFSgraph2.addVertex(we);
	cout << "Was up UFO\n";
	
	return(0);
}