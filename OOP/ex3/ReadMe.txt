								LIGHTS
EX3	::	EX3||EX3	: :		EX3||EX3	: :		EX3||EX3 ::	EX3||EX3	::	EX3
*******************************************************************************
								
Hadassah college:
Computer since	2011	Semecter B
Object oriented programing Simester B Year 2011(2010)
*******************************************************************************

Students Info:
ex3-andreysh_iliaga

	#	id:	321470882	Andrey Shamis	-	andreysh
	#	id:	309480051	Ilia Gaysinsky	-	iliaga
*******************************************************************************

User guide:

	Keyboard Control:
	
		q	-	Load quadre graph game.
		h	-	Load hex graph game.
		s	-	Show solution of curent game.
		n	-	Replay curent game - thats mean new game with new solution way.
		l	-	Go up by level whitout playing small levels
		x	-	Exit from the Game.
		
	
*******************************************************************************
The Game -  Lights. 

	The game is to solve - finding a solution for spanning tray. Although the 
tree itself is in the box but at the same vertex are in disarray and edges 
broken on two. 
	To solve the need to twist the vertex on its axis. So what would 
brokenness edges are facing each other in the correct order. As a result, 
we need to bridge the so all vertices that would be current with an average 
hit at the top of the others. And so it is necessary to pass a certain number 
of levels and there are two kinds of graphs.

*******************************************************************************
Game Architecture/Data structure/Some algoritms:

	For storage levels - the status of the game, we use a class that was 
written by us in the last assignment, for storing graphs. 

	On the instructions required to create two types of games, the first 
type of view of the square, votoroy type due to the hexagon. We have two 
algorithms for constructing these graphs. Each algorithm produces the 
desired shape at the same time creates an edge between the vertices 
of the graph. 

	Once we got the graph (you can call this graph the full - even though he 
is not quite complete), we run an algorithm that randomly returns a random 
vertex of the graph, it uses an iterator for the exact same graph written 
by us. 
	After that, we run the algorithm for the DFS to that summit which gave 
us the algorithm for random pooling vertices of the graph. Once we have 
received the vector DFS order of the vertices, we need to remove all the 
edges in the graph and put only those edges that create a graph 
algorithm after DFS

For this algorithm is used which does the following, it puts an edge 
between two vertices according to the algorithm DFS, as well as on the 
physical two-dimensional arrangement of the vertices of sets of points 
according to the angle deviation of one vertex from each other. 
	These data are stored in the vertices themselves, and therefore these 
data, we then during the game will decide where and where an edge is added 
to delete. 

	And so we got ready to count for the game. After that, we use the entire 
graph iterator looping over all vertices and randomly random Number of times 
we turn the top around its axis, that actually appeal to a vector containing 
the data and every time we take from the beginning of the vector and the 
value we put in the end. 
	Now we have a graph that make up our game. Now we look forward to 
pressing on the player, cool top on which he pressed around its axis once 
and call the main algorithm that is depending of type 
defined by the angle of inclination relative to the other top decide if 
whether or not to put an edge between them. In this appeal goes only to the 
neighbors some vertex, and we know this thanks to the fact that the 
original graph we hold that to know who is a neighbor to whom. 
And also we have an iterator to traverse the neighbors definition 
of the vertices.

After a player clicks on a vertex and we shook, and put ribs in the 
right places, we run a different algorithm with the BFS source advocates 
the middle vertex of the graph.
Still, it remains only draw all vertex and it is important to indicate that 
the BFS algorithm during run "lights" on the right vertex, and thus every 
vertex knows if it burns("Lighted") or not.


*******************************************************************************

Noteable Algoritms:

	One of the important algorithms in the game is an algorithm for affixing 
the edges of the graph depending on the angle of finding two vertices.

Level creation! Is also the main level creation. 
Firstly the choice of vertices is random. 
Secondly during the build (passage DFS) spaning tree from a neighbor's 
neighbors is chosen randomly. 

Ie the number of possible games for any level or any type of game is 
very great just great! 

For example, for a square game length five the number of possible levels 
of 98 ^ 3 * 12 = 11294304.

******************************************************************************
Created Files:

	ex3.sln				Project file
	ex3.vcproj			Project file
	GameController.cpp	Game controller class
	GameController.h	Game controller header
	Graph.h				Graph class file
	macros.h			Macros
	main.cpp			Main file
	ReadMe.txt			Radme file
	Vertex.cpp			Vertex file cpp
	Vertex.h			Vertex header
*******************************************************************************
Knowns bugs
				No known bugs!
			