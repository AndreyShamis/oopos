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

	//someGraph.setUniq_values(true);
	int data = 10;
	int ver_size = 6;
	for(int i = 0;i<ver_size;i++)
	{
		int id = someGraph.addVertex(data+i);
		//cout << "NUMBER:\t" << id << "\t \t VALUE:\t" << data*i+1 << "\n";
	}
	cout << "Builded\n";
	/*int x = 15;
	for(int i = 0;i<ver_size;i+=1)
	{
		x*=7;
		someGraph.addEdge(i,ver_size-i*ver_size%6);
		someGraph.addEdge(i+(((ver_size-3)*(ver_size-1)*i)%ver_size),(i*i)%11);
		someGraph.addEdge((i-(i*3)%(ver_size-1))%ver_size,i*i%7);
		someGraph.addEdge(i+(((ver_size-6)*(ver_size-1)*i)%ver_size),(i*x)%11);
		someGraph.addEdge((x-(x*3)%(ver_size-1))%ver_size,i*i%7);
	}*/
	//for(int i = 1;i<ver_size+1;i++)
	//{
	//	for(int j = 1;j<ver_size+1;j++)
	//	{
	//		someGraph.addEdge(i,i+i);
	//	}
	//}
	someGraph.addEdge(1,2);
	someGraph.addEdge(1,6);
	someGraph.addEdge(2,4);
	someGraph.addEdge(4,6);
	someGraph.addEdge(5,3);

//####################################################################
//## OBA ALGORITMA RABOTAUT _ ZASHEBIS!!!!!!!!!!!!!! -- NO PROVER!!!##
//##================================================================##
//####################################################################


	//+++++++++++++++++++++++++++DFS TEST+++++++++++++++++++++++++++++++++++//

	cout << "Print: DFS\n";			
	someGraph.printDFS(2);


	//+++++++++++++++++++++++++++BFS TEST+++++++++++++++++++++++++++++++++++//

	cout << "Print: BFS\n";
	someGraph.printBFS(2);








	//someGraph.addVertex(78);
	//someGraph.addVertex(78);
	//someGraph.addVertex(78);
	//someGraph.addVertex(78);
	//someGraph.addVertex(78);
	//someGraph.addVertex(78);
	//someGraph.addVertex(78);


	//someGraph.addEdge(7,3);

	//someGraph.detachVertex(4); 

	//someGraph.removeEdge(1,1);

	//someGraph.removeVertex(2);

	

	//someGraph.printDFS(1);
	int **matr = someGraph.getMatrixRepresentation();

	for(int i=0;i<someGraph.countNodes()+1;i++)
	{
		for(int j=0;j<someGraph.countNodes()+1;j++)
			cout  << setw(2) << matr[i][j];

		cout << "\n";

	}
	cout << "Edges size " << someGraph.countEdges() << ".\n";
	cout << "Nodes count " << someGraph.countNodes() << "\n";

//_________________________________________________________________



	//someGraph.removeVertex(2);


	/*matr = someGraph.getMatrixRepresentation();
	for(int i=0;i<someGraph.countNodes()+1;i++)
	{
		for(int j=0;j<someGraph.countNodes()+1;j++)
			cout  << setw(2) << matr[i][j];

		cout << "\n";

	}*/
	//cout << "Edges size " << someGraph.countEdges() << ".\n";
	//cout << "Nodes count " << someGraph.countNodes() << "\n";

	for(int i = 0;i<200000;i++)
	{
		if(someGraph.getIDbyValue(i))
			cout << "NUMBER:\t" << i << "\t" << someGraph.getIDbyValue(i) << "\n";
	}
////_________________________________________________________________
//	someGraph.removeVertex(1);
//
//
//	matr = someGraph.getMatrixRepresentation();
//	for(int i=0;i<someGraph.countNodes()+1;i++)
//	{
//		for(int j=0;j<someGraph.countNodes()+1;j++)
//			cout  << setw(2) << matr[i][j];
//
//		cout << "\n";
//
//	}
//	cout << "Edges size " << someGraph.countEdges() << ".\n";
//	cout << "Nodes count " << someGraph.countNodes() << "\n";




	//someGraph.addVertex(data);
	/*int f = someGraph.addVertex(data);
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

	


	*/


	return(0);
}