
#include "macros.h"
#include "bar.h"

Bar::Bar()
{
	;
}


void Bar::Draw()
{
	glBegin(GL_QUADS); // Start drawing a quad primitive

	glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner
	glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner
	glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner
	glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner

	glEnd();
}