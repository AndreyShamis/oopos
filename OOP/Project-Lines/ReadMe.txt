								Lines
							Poject of semester B
*******************************************************************************
								
Hadassah college:
Computer since	2011	Semecter B
Object oriented programing Simester B Year 2011(2010)
*******************************************************************************

Students Info:

	#	id:	321470882	Andrey Shamis	-	andreysh
	#	id:	309480051	Ilia Gaysinsky	-	iliaga
*******************************************************************************

User guide:

	Mouse control 
		Press right botton.
		
	Keyboard Control:
		q	-	Exir from the game
		n	-	New game
		h	-	Show help
	
*******************************************************************************
The Game -  Lines. 

Game lines of the game is that you must collect a number is not important as: 
whether it is a string either in a column that is generally measured 
diagonally five or more balls. 

	Balls come in different colors, most of the balls is a simple color, 
yet there are several kinds of mixed beads, 
one kind of ball that contains all the colors and that can be included in 
a set with any other balls, as well as the bomb which has properties 
identical to the mixed bead which contains all colors, but the only 
difference is that the bomb during that bomb as part of a set of balls, 
it also allows, and removes the balls that are in its terms, within a 
radius of One unit.

Successful indicator of the game is the number of points accumulated by you.


*******************************************************************************
Game Architecture/Data structure:

In our program we use the following data structures are as follows: 
Graf, Map, Vector. 
Graph is used to the fact that it would be stored cell field, which we run 
the algorithm for finding the shortest path between the outcome and 
the ball go where we want to put it. 
	The algorithm for finding the shortest path in the graph was added to 
our class that we wrote a second job. 
	Map is used by us for balls, namely the fact that to know the two keys
where one or the other ball. 

	Note that those balls that are in the map are those balls that we draw 
on the cells of themselves playing field, that is, when we add the 
ball to the map we also make a temporary shutdown of all edges of the cell 
to which is in the box thus represents the algorithm of finding the shortest 
path already or does not pass through this cell to that as it is a ball. 

	It is also worth noting that there are other balls Ktorov drawn during 
the game, namely that the balls next time put on the field, then 
there are those who see the mono to the right during the game standing 
in the column. These pellets are stored in a vector, since we did not 
do when they find important and we did not order the balls inside the vector.

	Another place to store the balls is the last vector, the latter in the 
sense that the balls that disappear from the field, at which time does 
not fit into this vector, the animation - drawing disappears from the 
field, and because they no longer act on the algorithm for finding a path 
as well as the fact that their position may drop another ball, we keep 
them in this vector. Note also that the vector is cleared by itself, 
meaning it has the highest and lowest limits, according to which he 
knows how much balls must be removed from this vector.

	And finally, the last vector is a vector that is used by the image of 
all the balls we have in the game. At the time that when a new ball, 
it is copied from the ball, depending on the color, which is located in 
the vector.

	The game is also present pleasant music that plays in the background. 
Also, there are sounds of events not properly attempt to put the ball, 
picking up the set, as well as if the set was previously collected, that is, 
if you built a set for the second time will be a different sound, so there 
is still sound and the appearance of other sounds.

	The game also has a system of points. Points are considered constant, 
which can be changed. Math scores depends on many factors, such as how 
many balls you have collected, how many times you have collected 
consecutive sets.
*******************************************************************************

Noteable Algoritms:

			***		Single shortest path	***
	An algorithm is an algorithm for finding the shortest path in graph 
between two vertices. As previously mentioned algorithm is needed to find a 
way that is backlit to drop the ball on the field playing. All of this 
algorithm mentioned above.

			***		FindRow Cols		***
	Also an important finding algorithm is an algorithm for finding a 
set of balls composes for removal from the field. The algorithm compares 
the balls, depending on their location and occurrence in the set, 
as well as their color.
	
			***		Garbage COllector		***
	As mentioned earlier, we have a vector of balls that have already 
completed or carry out the animation or still hold, so this algorithm 
is a janitor of this balls from this vector.


******************************************************************************
Created Files:
Ball.cpp
Ball.h
BlackBall.cpp
BlackBall.h
BlueBall.cpp
BlueBall.h
Board.cpp
Board.h
BombBall.cpp
BombBall.h
Config.h
Dragable.cpp
Dragable.h
Drawable.cpp
Drawable.h
Floor.cpp
Floor.h
GameController.cpp
GameController.h
Grafic.cpp
Grafic.h
Graph.h
GreenBall.cpp
GreenBall.h
GreenYellowBall.cpp
GreenYellowBall.h
macros.h
main.cpp
MixedBall.cpp
MixedBall.h
OrangeBall.cpp
OrangeBall.h
OrangeRedBall.cpp
OrangeRedBall.h
ReadMe.txt
RedBall.cpp
RedBall.h
Sprite.cpp
Sprite.h
WhiteBall.cpp
WhiteBall.h
WhiteBlueBall.cpp
WhiteBlueBall.h
YellowBall.cpp
YellowBall.h

*******************************************************************************
Knowns bugs
				No known bugs!
			