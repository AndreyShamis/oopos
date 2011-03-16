EX2		EX2		EX2		EX2		EX2			
*******************************************************************************
*******************************************************************************

***************************************
Hadassah college:
Computer since	2011	Semecter B
Object oriented programing Simester B Year 2011(2010)


*****************************************************

Students Info:
**************
ex2-andreysh_iliaga
		
	#	id:	309480051	Ilia Gaysinsky	-	iliaga
	#	id:	321470882	Andrey Shamis	-	andreysh
	
	#	All rights reserved  ©



General explanation of the exercise:
************************************

A program that realized
allowd the faloing options:

- creat shapes: circle, empty circle, rectangke, empty rectangle, wheel, dot,
		square, Icuale side triangle, iquangular, vertical side, 
		horizontal side.
- resize shapes
- select privius and next shape - for eding or delete shapes
- clear: clear selected shapes by same color, cler selected shape, by same 
	 type, clear all.
- set color.
- select shape to drow.
- remove mark of selected shape
- undo.


List of files that been created:									
********************************
circle.cpp				//Circle
Circle.h
Dot.cpp					//	Dor
Dot.h
EmptyCircle.cpp			//	Empty circle
EmptyCircle.h
EmptyRectangle.cpp		//	Empty rectangle
EmptyRectangle.h
Equiangular.cpp			//	Equiangular
Equiangular.h
Error.wav				//	Sound file
ex1.sln					//	Solution file
Horizontal.cpp			//	Horizontal line
Horizontal.h
Itriangle.cpp			//	Itriangle
Itriangle.h
macros.h				//	Mactros and setings
main.cpp				//	Main file
Paint.cpp				//	Main class file
Paint.h
Rectanglle.cpp			//	Rectanglle
Rectanglle.h
Shape.cpp				//	Shape
Shape.h
Square.cpp				//	Square
Square.h
UML.jpg					//	UML FILE
Vertical.cpp			//	Vertical
Vertical.h
Wheel.cpp				//	Wheel
Wheel.h

User guide:
***********


#	HOW TO USE:	
		- press right botton on the program window to select wanted 
		  option.
		- press left botton on the program wondow to place chosen 
		  shape

	there is another option to control the program - Keyboard  Control:


	key			function
	--------------------------------------------------
	Ctrl+ 			Grow Selected
	- 			Shrink selected
	Ctrl_			Change size to same shapes
	Del			Delete selected
	Shift+z			Select previous
	Shift+x			Select next
	Space			Unselect selected
	Shift+a			Delete all
	Shift+c			Delete all by same color
	Shfi+t			Delete all to same types
	ESC			Exit program
						
	

Main data structures and their functionality:
*********************************************
In the program used
	*	-	VECTOR.
	*	-	Struct of color to create color.
	*	-	Vector of undo.

Notable algorithms:												
*******************
	See the next paragraph-->> which describe interesting points
	
	>>>>
Interesting points:															
*******************
<<<<<UNDO>>>>>
Undo - Ctrl+z
Have function for 4 types of undo changes

1	-	Undo for selection
2	-	Undo for created object
3	-	Undo for deleted object/s
4	-	Undo for changed object/s

	The all 4 types of undo worked by not same way:
#	-Undo selection used only one integer.
#	-Undo for created used only one pointer to created onject.
#	-Undo for changes have vector of status shape struct which save the 
propertis of changes chape.
#	-Undo for deleted object/s use same way like previous way.

Thats mean UNDO work for ALL options in the program and 
ALSO unclude Undo selection :) future. !It can be removed in a few clicks of 
the mouse, in case if this code to someone seriously need to be used in 
serious applications. And "because" beauty-work its used in this version.


<<<<<SOUND>>>>>>
Sound on errors
Have only one sound track.This annoying track borrowed from Microsoft.
Used when user trying to do same action or event on non selected object or
make/run unavilable function.For disable the function of sound just comment
the line in code to play sound.

Recomedation: disable sound for good Glut work!!!
Any problems with program speed may be caused by using sound!


<<<<<Keyboard  Control>>>>>>
- see User guide


/------------------------------------------------------------------------------
SINGLETON
The class Paint is a singleton object. Becouse we run it only one time.
For get instance use function getInst().

/------------------------------------------------------------------------------

Design/UML:														
*******		
We have diagrams with design of the program.				
================== >>>> UML.jpg

Known bugs:
***********

		NO BAGS!!! The program work very well!!!
-------------------------------------------------------------------------------