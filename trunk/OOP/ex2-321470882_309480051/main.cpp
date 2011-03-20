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

#include <iomanip>
using namespace std;


//=============================================================================
//	Main function
int main()
{
	//typedef Graph<struct BFS_node> someGraph();
	Graph<int> someGraph;

	
	//BFS_node kodkod;
	//kodkod._value = 0.01;

	int data = 10;
	int ver_size = 10;
	for(int i = 0;i<ver_size;i++)
	{
		int id = someGraph.addVertex(data*i+1);
		cout << "NUMBER:\t" << id << "\t \t VALUE:\t" << data*i+1 << "\n";
	}
	int x = 15;
	for(int i = 0;i<ver_size;i+=1)
	{
		x*=7;
		someGraph.addEdge(i,ver_size-i*ver_size%6);
		someGraph.addEdge(i+(((ver_size-3)*(ver_size-1)*i)%ver_size),(i*i)%11);
		someGraph.addEdge((i-(i*3)%(ver_size-1))%ver_size,i*i%7);
		someGraph.addEdge(i+(((ver_size-6)*(ver_size-1)*i)%ver_size),(i*x)%11);
		someGraph.addEdge((x-(x*3)%(ver_size-1))%ver_size,i*i%7);
	}
	someGraph.printDFS(1);
	int **matr = someGraph.getMatrixRepresentation();

	for(int i=0;i<someGraph.countNodes()+1;i++)
	{
		for(int j=0;j<someGraph.countNodes()+1;j++)
			cout  << setw(2) << matr[i][j];

		cout << "\n";

	}
	cout << "Edges size " << someGraph.countEdges() << ".\n";
	//someGraph.addVertex(data);
	int f = someGraph.addVertex(data);
	int s = someGraph.addVertex(data+2);
	int s1 = someGraph.addVertex(data+3);
	int s2 = someGraph.addVertex(data+5);
	someGraph.addVertex(data+6);
	someGraph.addVertex(data+1);
	
	cout << "Edges size " << someGraph.countEdges() << ".\n";
	if(!someGraph.addEdge(f,s))
		cout << "Not Added\n";

	if(!someGraph.addEdge(s1,s1))
		cout << "Not Added\n";

	
	cout << "Edges size " << someGraph.countEdges() << ".\n";
	someGraph.printBFS(data);
	
	if(!someGraph.removeVertex(s))
		cout << "Not Deleted\n";

	someGraph.printBFS(data);



	int s3 = someGraph.addVertex(data+5);
	cout << "Edges size " << someGraph.countEdges() << ".\n";

	if(!someGraph.addEdge(f,s3))
		cout << "Not Added\n";

	cout << "Edges size " << someGraph.countEdges() << ".\n";
	int s6 = someGraph.addVertex(data+125);
	someGraph.addEdge(s6,s6);
	someGraph.printBFS(data);


	

	if(someGraph.removeEdge(f,s3))
		cout << "Added\n";
	else
		cout << "Not Added\n";
	someGraph.removeEdge(s6,s6);

	


	


	return(0);
}