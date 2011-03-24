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



//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
List of files that been created:									
//=============================================================================

					
	
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Main data structures and their functionality:
//=============================================================================




//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Notable algorithms:												
//=============================================================================

	*** Set unique values Graph
Function wich provide function use the graph only with unique values.

	1)	First case work only if no found any vertex in graph.
	
	2)	Second case work only if the graph actualy is unique and 
have only unique value and you want to transform the graph to not 
unique value vertex.

	*** BFS (breadth-first search) 
the algorithem was build at the classic way (include all 3 colors of vertexes)
which leave the option for extantion of the algorithem to his real goal (like
builde breadth-first search Tree, calculation of shorter distanases from the 
sourse vertex to the leafs). practecly, there is no need of the black color in 
the algorithem (we do not need line 483 at file Graph:"state[vertex] = Black;")
because unfortunately the asaitmen did not tell to do full functioning Breadth-
First Search algorithem.

	*** DFS (Depth-first search)
the algorithem was build at the special recursiv way. there is main DFS 
function that initiat the algorithem (paint vertex to wight, translate the
real id of the sourse verte in thr vector of id's, and call the DFS main 
"angen" recursiv function - as aresult we do not need another data structur
like "queue" or "stak" that usualy used at DFS algorithem.practecly, there 
is no need of the black color in the algorithem we chenge the use of black 
color to gray color an as a result we use 2 colors, still we use 3 colores 
because of the same reasonse as discrib above at "BFS" chapter.
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







//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Design/UML:														
//=============================================================================		
We have diagrams with design of the program.				
================== >>>> UML.jpg



//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Known bugs:
//=============================================================================

		NO BAGS!!! The program work very well!!!
-------------------------------------------------------------------------------