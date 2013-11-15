#include "Texture.h"
#include "Shader.h"
#include "Object.h"
#include "Quadtree.h"

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

	glfwWindowHint(GLFW_SAMPLES, 16);
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "My Title", NULL, NULL);
	glfwMakeContextCurrent(window);

	ResourceHolder glfwHolder([&window]() { glfwDestroyWindow(window); glfwTerminate(); });

	if(glewInit() != GLEW_OK)
	{
		cerr <<"Failed to initialize GLEW" <<endl;
		return -1;
	}

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	Shader shader("..\\resources\\DemoShader");

	Quadtree objCollection;
	objCollection.Insert(std::make_shared<Object>(glm::vec3(0, 0, 0), glm::vec3(1.2, 1.2, 1.2), "..\\resources\\Gust.dds"));
	objCollection.Insert(std::make_shared<Object>(glm::vec3(-2, 0, 0), glm::vec3(1.2, 1.2, 1.2), "..\\resources\\Gust.dds"));

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double curTime = glfwGetTime();
		double timeSinceLastFrame = curTime - lastTime;
		lastTime = curTime;

		objCollection.Update(timeSinceLastFrame);

		double ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		ratio = width / (double)height;
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio * 6, ratio * 6, -1 * 6, 1 * 6, 10, -10);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		objCollection.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}