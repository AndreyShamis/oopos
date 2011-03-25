							EX2	===	Graph	
//=============================================================================
Hadassah college:
Computer since	2011	Semecter B
Object oriented programing Simester B Year 2011(2010)

//=============================================================================

Students Info:
//=============================================================================
ex2-andreysh_iliaga
		
	#	id:	309480051	Ilia Gaysinsky	-	iliaga
	#	id:	321470882	Andrey Shamis	-	andreysh

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
General explanation of the exercise:
//=============================================================================

This program is a turnkey solution for working with graphs. 
	The class can take any value, but it is important that if you decide to 
use a graph to store the other classes that should be, these classes were 
able to print yourself, you have had a print statement, and if you want 
that graph had the opportunity to be unique a fascist object must have 
a comparison operator. 

IMPORTANT:	If used to store unique values, the type that is stored in 
			the vertices must have a comparison operator!

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
List of files that been created:									
//=============================================================================

ex2-321470882_309480051.sln		//	project file
ex2-321470882_309480051.vcproj	//	project file

Graph.h					//	the graph header and programm
HadassahGraph.h			//	Hadassah file
macros.h				//	Hadassah file
ReadMe.txt				//	Readme
UML.jpg					//	UML file in jpg
ClassDiagram.cd			//	Class diagramm is the same file
					
	
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Main data structures and their functionality:
//=============================================================================
	In our class we use two data storage. 
In this case, the first vector is the storage of misuse of the data 
itself, and the second vector keeps a structure for each vertex in the graph. 

	The structure itself invaded vector stores data such as: serial number 
of vertices in the graph, and a list of neighbors of this vertex 
with the list of neighbors consists of serial numbers of neighbors. 

	Note that there is not any connection between the two vectors 
but if we remove any record from the realties of the first vector, or vice 
versa, we also remove parallel to the same record (in the same account 
which is at a certain distance from the beginning of the vector) to 
another vector. 

	And when you add a vertex in the graph is a similar situation by adding 
a vertex in the second vector while maintaining the structure of 
the vector, ie, the linear terms in the array. 

	After that, when we want to find a vertex of knowing only its sequence 
number, we are looking for it in the second vector, and then in 
the case of a determination, we take the position at which the record has 
been found and ask for exactly the same position in the first vector 
for the that would take from there the data.


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Notable algorithms:												
//=============================================================================

	*** Set unique values Graph
Function wich provide function use the graph only with unique values.

	1)	First case work only if no found any vertex in graph.
	
	2)	Second case work only if the graph actualy is unique and 
have only unique value and you want to transform the graph to not 
unique value vertex.
-------------------------------------------------------------------------------

	*** BFS (breadth-first search) 
the algorithem was build at the classic way (include all 3 colors of vertexes)
which leave the option for extantion of the algorithem to his real goal (like
builde breadth-first search Tree, calculation of shorter distanases from the 
sourse vertex to the leafs). 

	Practecly, there is no need of the black color in 
the algorithem (we do not need line 483 at file Graph:"state[vertex] = Black;")
because unfortunately the asaitmen did not tell to do full functioning Breadth-
First Search algorithem.
-------------------------------------------------------------------------------

	*** DFS (Depth-first search)
The algorithm was build at the special recursiv way.
There is main DFS function that initiat the algorithem 
(paint vertex to wight, translate the real id of the sourse vertex 
in thr vector of id's, and call the DFS main "angen" recursiv 
function - as aresult we do not need another data structur like "queue" 
or "stak" that usualy used at DFS algorithem.

	Practecly, there is no need of the black color in the algorithem 
we chenge the use of black color to gray color an as a result we use 2 
colors, still we use 3 colors because of the same reasonse as discribe
above at "BFS" chapter.
-------------------------------------------------------------------------------

	*** Select vertex by DATA value(getIDbyValue())
	Function wich can find some vertex by him value.
It is advisable to use this feature only if the graph is set 
to unique values.	
	Anyway the decision to use this feature being touted 
developer and in case of using the function the function returns 
a value ID for vertex in the first it finds that contains the 
specified value.

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Interesting points:															
//=============================================================================
IMPORTANT:	
			If used to store unique values, the type that is stored in 
			the vertices must have a comparison operator!

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Design/UML:														
//=============================================================================		
We have diagrams with design of the program.				
================== >>>> UML.jpg
or look for Class diagram in ClassDiagram.cd

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Known bugs:
//=============================================================================

		NO BAGS!!! The program work very well!!!
-------------------------------------------------------------------------------