#include "Texture.h"
#include "Shader.h"
#include "Object.h"
#include "Quadtree.h"

#include <iostream>

#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

bool _useQuadtree = true;
bool _drawQuadtreeGraph = false;

void OnKeyPress(GLFWwindow* /*window*/, int key, int /*scanCode*/, int action, int /*mods*/)
{
	if(action == GLFW_PRESS)
	{
		switch(key)
		{
		case GLFW_KEY_Q:
			_useQuadtree = !_useQuadtree;
			break;
		case GLFW_KEY_D:
			_drawQuadtreeGraph = !_drawQuadtreeGraph;
			break;
		}
	}
}

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, OnKeyPress);

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

	const double WINDOW_MAX_X = 10, WINDOW_MAX_Y = WINDOW_MAX_X * 1080 / 1920;

	vector<std::shared_ptr<Object>> masterList;
	for(int i=0;i<200;++i)
	{
		double randx = double(rand() % int(WINDOW_MAX_X * 100 * 2) - (WINDOW_MAX_X * 100) ) / 100;
		double randy = double(rand() % int(WINDOW_MAX_Y * 100 * 2) - (WINDOW_MAX_Y * 100) ) / 100;
		masterList.push_back(std::make_shared<Object>(glm::vec3(randx, randy, 0), glm::vec3(0.3, 0.3, 0.3), "..\\resources\\Gust.dds", true));
	}

	masterList.push_back(std::make_shared<Object>(glm::vec3(0, -7, 0), glm::vec3(25, 4, 1), std::string(), false));
	
	double lastTime = glfwGetTime(), framerateStartTime = lastTime;

	int frameCount = 0;

	while (!glfwWindowShouldClose(window))
	{
		double curTime = glfwGetTime();
		double timeSinceLastFrame = curTime - lastTime;
		lastTime = curTime;

		++frameCount;

		//Check and display the FPS every 5 seconds
		if(curTime >= framerateStartTime + 5)
		{
			double fps = double(frameCount) / (curTime - framerateStartTime);
			cout <<"FPS: " <<fps <<endl;
			frameCount = 0;
			framerateStartTime = curTime;
		}

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
		glOrtho(-WINDOW_MAX_X, WINDOW_MAX_X, -WINDOW_MAX_Y, WINDOW_MAX_Y, 10, -10);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		if(_useQuadtree)
		{
			//Since the quadtree will move with the camera, we'll have to re-insert most objects most frames anyway
			//  Rather than including logic to only re-insert needed objects, just re-insert every object every frame
			Quadtree objCollection(glm::vec3(0, 0, 0), WINDOW_MAX_X * 2, WINDOW_MAX_Y * 2);
			std::for_each(std::begin(masterList), std::end(masterList), [&objCollection](decltype(*std::begin(masterList)) obj)
			{
				objCollection.Insert(obj.get());
			});
			objCollection.Update(timeSinceLastFrame);
			objCollection.Draw(_drawQuadtreeGraph);
		}
		else
		{
			foreach(masterList, std::bind(&Object::Update, std::placeholders::_1, timeSinceLastFrame));

			for(auto iObj = std::begin(masterList); iObj < std::end(masterList); ++iObj)
			{
				for(auto jObj = iObj + 1; jObj < std::end(masterList); ++jObj)
				{
					if((*iObj)->DoesCollide(*jObj))
					{
						(*iObj)->HandleCollision(*jObj);
						(*jObj)->HandleCollision(*jObj);
					}
				}
			}

			foreach(masterList, std::bind(&Object::Draw, std::placeholders::_1));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}