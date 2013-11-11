#include "Texture.h"
#include "Shader.h"

#include <iostream>

#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main(int argc, char** argv)
{
	if(!glfwInit())
	{
		cerr <<"Failed to initialize GLFW" <<endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "My Title", NULL, NULL);
	glfwMakeContextCurrent(window);

	ResourceHolder glfwHolder([&window]() { glfwDestroyWindow(window); glfwTerminate(); });

	if(glewInit() != GLEW_OK)
	{
		cerr <<"Failed to initialize GLEW" <<endl;
		return -1;
	}

	glEnable(GL_TEXTURE_2D);

	Texture tex("..\\resources\\Gust.dds");
	Shader shader("..\\resources\\DemoShader");

	while (!glfwWindowShouldClose(window))
	{
		double ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		ratio = width / (double)height;
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio * 3, ratio * 3, -1 * 3, 1 * 3, 1, -1);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef((float) glfwGetTime() * 50, 0, 0, 1);

		{
			auto texHolder = tex.ActivateScoped();
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glColor3f(1, 0, 0);
			glVertex3f(-0.6f, -0.6f, 0);
			glTexCoord2f(1, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0.6f, -0.6f, 0);
			glTexCoord2f(1, 1);
			glColor3f(0, 0, 1);
			glVertex3f(0.6f, 0.6f, 0);
			glTexCoord2f(0, 1);
			glColor3f(1, 1, 0);
			glVertex3f(-0.6f, 0.6f, 0);
			glEnd();
		}

		{
			auto shaderHolder = shader.ActivateScoped();
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0.6f, -0.6f, 0);
			glTexCoord2f(1, 0);
			glColor3f(1, 0, 0);
			glVertex3f(1.8f, -0.6f, 0);
			glTexCoord2f(1, 1);
			glColor3f(1, 1, 0);
			glVertex3f(1.8f, 0.6f, 0);
			glTexCoord2f(0, 1);
			glColor3f(0, 0, 1);
			glVertex3f(0.6f, 0.6f, 0);
			glEnd();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}