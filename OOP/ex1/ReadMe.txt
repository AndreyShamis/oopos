
Keyboard  Control
-------------------------------------------------------------------------------
Ctrl+ 	Grow Selected
-		Shrink selected
Ctrl_	Change size to same shapes
Del		Delete selected
Shift+z	Select previous
Shift+x	Select next
Space	Unselect selected
Shift+a	Delete all
Shift+c	Delete all by same color
Shfi+t	Delete all to same types
ESC		Exit program


Points
/------------------------------------------------------------------------------
UNDO
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

/------------------------------------------------------------------------------
SOUND
Sound on errors
Have only one sound track.This annoying track borrowed from Microsoft.
Used when user trying to do same action or event on non selected object or
make/run unavilable function.For disable the function of sound just comment
the line in code to play sound.

Recomedation: disable sound for good Glut work!!!
Any problems with program speed may be caused by using sound!

/------------------------------------------------------------------------------
SINGLETON
The class Paint is a singleton object. Becouse we run it only one time.
For get instance use function getInst().

/------------------------------------------------------------------------------
