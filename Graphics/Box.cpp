#include "Box.h"

#include <GL/glew.h>

Box::Box()
{
}

void Box::Draw()
{
	glBegin(GL_QUADS);

	//Front face
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.5, 0.5);

	//Left face
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.5, -0.5);

	//Back face
	glTexCoord2f(0, 1);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.5, -0.5);

	//Right face
	glTexCoord2f(0, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();
}