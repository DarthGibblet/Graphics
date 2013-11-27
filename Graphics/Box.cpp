#include "Box.h"

#include <GL/glew.h>

Box::Box()
{
}

void Box::Draw(const bool drawBackwards)
{
	glBegin(GL_QUADS);

	double leftTextCoord = drawBackwards ? 1 : 0,
		rightTextCoord = drawBackwards ? 0 : 1;

	//Front face
	glTexCoord2d(leftTextCoord, 1);
	glVertex3d(-0.5, -0.5, -0.5);
	glTexCoord2d(rightTextCoord, 1);
	glVertex3d(0.5, -0.5, -0.5);
	glTexCoord2d(rightTextCoord, 0);
	glVertex3d(0.5, 0.5, -0.5);
	glTexCoord2d(leftTextCoord, 0);
	glVertex3d(-0.5, 0.5, -0.5);

	////Left face
	//glTexCoord2f(leftTextCoord, 1);
	//glVertex3f(-0.5, -0.5, 0.5);
	//glTexCoord2f(rightTextCoord, 1);
	//glVertex3f(-0.5, -0.5, -0.5);
	//glTexCoord2f(rightTextCoord, 0);
	//glVertex3f(-0.5, 0.5, -0.5);
	//glTexCoord2f(leftTextCoord, 0);
	//glVertex3f(-0.5, 0.5, 0.5);

	////Back face
	//glTexCoord2f(leftTextCoord, 1);
	//glVertex3f(0.5, -0.5, 0.5);
	//glTexCoord2f(rightTextCoord, 1);
	//glVertex3f(-0.5, -0.5, 0.5);
	//glTexCoord2f(rightTextCoord, 0);
	//glVertex3f(-0.5, 0.5, 0.5);
	//glTexCoord2f(leftTextCoord, 0);
	//glVertex3f(0.5, 0.5, 0.5);

	////Right face
	//glTexCoord2f(leftTextCoord, 1);
	//glVertex3f(0.5, -0.5, -0.5);
	//glTexCoord2f(rightTextCoord, 1);
	//glVertex3f(0.5, -0.5, 0.5);
	//glTexCoord2f(rightTextCoord, 0);
	//glVertex3f(0.5, 0.5, 0.5);
	//glTexCoord2f(leftTextCoord, 0);
	//glVertex3f(0.5, 0.5, -0.5);

	glEnd();
}