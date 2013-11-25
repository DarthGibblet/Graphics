#include "Texture.h"
#include "Shader.h"
#include "Object.h"
#include "Bullet.h"
#include "Camera.h"
#include "Quadtree.h"

#include <iostream>

#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

bool _useQuadtree = true;
bool _drawQuadtreeGraph = false;
bool _pushLeft = false;
bool _pushRight = false;
bool _jump = false;
bool _shouldClose = false;

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
		case GLFW_KEY_LEFT:
			_pushLeft = true;
			break;
		case GLFW_KEY_RIGHT:
			_pushRight = true;
			break;
		case GLFW_KEY_SPACE:
			_jump = true;
			break;
		case GLFW_KEY_ESCAPE:
			_shouldClose = true;
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

	const double ZONE_MAX_X = 13, ZONE_MAX_Y = 6;

	vector<std::shared_ptr<Object>> masterList;
	//for(int i=0;i<200;++i)
	//{
	//	double randx = double(rand() % int(ZONE_MAX_X * 100 * 2) - (ZONE_MAX_X * 100) ) / 100;
	//	double randy = double(rand() % int(ZONE_MAX_Y * 100 * 2) - (ZONE_MAX_Y * 100) ) / 100;
	//	masterList.push_back(std::make_shared<Object>(glm::vec3(randx, randy, 0), glm::vec3(0.3, 0.3, 0.3), "..\\resources\\Gust.dds", true, Object::Type::Bullet));
	//}

	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	double ratio = (double)frameBufferHeight / frameBufferWidth;
	Camera cam(10, ratio);

	auto player = std::make_shared<Object>(glm::vec3(0, 5, 0), glm::vec3(1, 1, 1), "..\\resources\\Gust.dds", true, Object::Type::Player);

	cam.Teather(player.get());
	cam.SetRestrictLeft(-ZONE_MAX_X);
	cam.SetRestrictRight(ZONE_MAX_X);
	cam.SetRestrictTop(ZONE_MAX_Y);
	cam.SetRestrictBottom(-ZONE_MAX_Y);

	auto enemy = std::make_shared<Object>(glm::vec3(-3, -4, 0), glm::vec3(0.25, 0.25, 0.25), "..\\resources\\Gust.dds", false, Object::Type::Enemy);
	enemy->Vel(glm::vec3(0.25, 0, 0));

	std::shared_ptr<Object> bullet = std::make_shared<Bullet>(glm::vec3(-4, -4, 0), glm::vec3(0.5, 0, 0), "..\\resources\\Gust.dds", player.get());

	masterList.push_back(std::make_shared<Object>(glm::vec3(0, -7, 0), glm::vec3(26, 4, 1), std::string(), false, Object::Type::Block));
	masterList.push_back(std::make_shared<Object>(glm::vec3(3, 0, 0), glm::vec3(1, 10, 1), std::string(), false, Object::Type::Block));
	masterList.push_back(player);
	masterList.push_back(enemy);
	masterList.push_back(bullet);
	
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

		if(_pushLeft)
		{
			player->Vel() += glm::vec3(-1, 0, 0);
			_pushLeft = false;
		}
		if(_pushRight)
		{
			player->Vel() += glm::vec3(1, 0, 0);
			_pushRight = false;
		}
		if(_jump)
		{
			player->Vel() += glm::vec3(0, 1, 0);
			_jump = false;
		}

		double ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		ratio = width / (double)height;
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		masterList = std::vector<std::shared_ptr<Object>>(std::begin(masterList), std::remove_if(std::begin(masterList), std::end(masterList), [](std::shared_ptr<Object> obj) -> bool
		{
			return !obj->IsAlive();
		}));

		if(_useQuadtree)
		{
			//Since the quadtree will move with the camera, we'll have to re-insert most objects most frames anyway
			//  Rather than including logic to only re-insert needed objects, just re-insert every object every frame
			Quadtree objCollection(glm::vec3(0, 0, 0), ZONE_MAX_X * 2, ZONE_MAX_Y * 2);
			std::for_each(std::begin(masterList), std::end(masterList), [&objCollection](decltype(*std::begin(masterList)) obj)
			{
				objCollection.Insert(obj.get());
			});
			objCollection.Update(timeSinceLastFrame);
			if(_drawQuadtreeGraph)
				objCollection.Draw();
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
		}

		cam.Update(timeSinceLastFrame);
		cam.Draw();

		foreach(masterList, std::bind(&Object::Draw, std::placeholders::_1));

		glfwSwapBuffers(window);
		glfwPollEvents();

		if(_shouldClose)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

	return 0;
}