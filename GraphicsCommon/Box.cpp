#include "Box.h"

#include <GL/glew.h>

Box::Box()
{
}

void Box::Draw(const bool drawBackwards)
{
	glBegin(GL_QUADS);

	double leftTextCoord = drawBackwards ? 1 : 0,
		rightTextCoord = drawBackwards ? 0 : 1,
		topTextCoord = 1,
		bottomTextCoord = 0;

	//glTexCoord2d(leftTextCoord, topTextCoord);
	//glVertex3d(-0.5, -0.5, -0.5);
	//glTexCoord2d(rightTextCoord, topTextCoord);
	//glVertex3d(0.5, -0.5, -0.5);
	//glTexCoord2d(rightTextCoord, bottomTextCoord);
	//glVertex3d(0.5, 0.5, -0.5);
	//glTexCoord2d(leftTextCoord, bottomTextCoord);
	//glVertex3d(-0.5, 0.5, -0.5);

	glTexCoord2d(leftTextCoord, topTextCoord);
	glVertex3d(-0.5, -0.5, -0.5);
	glTexCoord2d(rightTextCoord, topTextCoord);
	glVertex3d(0.5, -0.5, -0.5);
	glTexCoord2d(rightTextCoord, bottomTextCoord);
	glVertex3d(0.5, 0.5, -0.5);
	glTexCoord2d(leftTextCoord, bottomTextCoord);
	glVertex3d(-0.5, 0.5, -0.5);

	glEnd();
}