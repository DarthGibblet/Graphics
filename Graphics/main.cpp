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

void ToggleUsingQuadtree()
{
	_useQuadtree = !_useQuadtree;
}

void ToggleDrawingQuadtree()
{
	_drawQuadtreeGraph = !_drawQuadtreeGraph;
}

void PushLeft()
{
	_pushLeft = true;
}

void StopLeft()
{
	_pushLeft = false;
}

void PushRight()
{
	_pushRight = true;
}

void StopRight()
{
	_pushRight = false;
}

void Jump()
{
	_jump = true;
}

void ShouldCloseWindow()
{
	_shouldClose = true;
}

void OnKeyPress(GLFWwindow* /*window*/, int key, int /*scanCode*/, int action, int /*mods*/)
{
	//Just throw out repeat actions. We're only interested in GLFW_PRESS and GLFW_RELEASE
	if(action == GLFW_REPEAT)
		return;

	typedef std::function<void()> keypress_func_t;
	static keypress_func_t _keyDownActions[GLFW_KEY_LAST];
	static keypress_func_t _keyUpActions[GLFW_KEY_LAST];
	static bool _initialized = false;
	if(!_initialized)
	{
		for(int i=0;i<GLFW_KEY_LAST; ++i)
		{
			_keyDownActions[i] = keypress_func_t();
			_keyUpActions[i] = keypress_func_t();

			_keyDownActions[GLFW_KEY_Q] = &ToggleUsingQuadtree;
			_keyDownActions[GLFW_KEY_D] = &ToggleDrawingQuadtree;
			_keyDownActions[GLFW_KEY_LEFT] = &PushLeft;
			_keyUpActions[GLFW_KEY_LEFT] = &StopLeft;
			_keyDownActions[GLFW_KEY_RIGHT] = &PushRight;
			_keyUpActions[GLFW_KEY_RIGHT] = &StopRight;
			_keyDownActions[GLFW_KEY_SPACE] = &Jump;
			_keyDownActions[GLFW_KEY_ESCAPE] = &ShouldCloseWindow;

		}
		_initialized = true;
	}

	auto& actionToPerform = action == GLFW_PRESS ? _keyDownActions[key] : _keyUpActions[key];

	if(actionToPerform)
		actionToPerform();
}

int main(int argc, char** argv)
{
	if(!glfwInit())
	{
		cerr <<"Failed to initialize GLFW" <<endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 16);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
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

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_STENCIL);
	glEnable(GL_STENCIL_TEST);

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

	auto player = std::make_shared<Object>(glm::vec3(0, 5, 0), glm::vec3(0.8, 1, 1), "..\\resources\\Gust.dds", true, Object::Type::Player);

	cam.Teather(player.get());
	cam.SetRestrictLeft(-ZONE_MAX_X);
	cam.SetRestrictRight(ZONE_MAX_X);
	cam.SetRestrictTop(ZONE_MAX_Y);
	cam.SetRestrictBottom(-ZONE_MAX_Y);

	auto enemy = std::make_shared<Object>(glm::vec3(-3, -2.5, 0), glm::vec3(5*0.8, 5, 5), "..\\resources\\Gust.dds", false, Object::Type::Enemy);
	enemy->Vel(glm::vec3(0.25, 0, 0));

	std::shared_ptr<Object> bullet = std::make_shared<Bullet>(glm::vec3(-6, -4, 0), glm::vec3(0.5, 0, 0), "..\\resources\\Bullet.dds", player.get());

	masterList.push_back(std::make_shared<Object>(glm::vec3(0, -7, 0), glm::vec3(26, 4, 1), std::string(), false, Object::Type::Block));
	masterList.push_back(std::make_shared<Object>(glm::vec3(3, 0, 0), glm::vec3(1, 10, 1), std::string(), false, Object::Type::Block));
	masterList.push_back(std::make_shared<Object>(glm::vec3(-13, 0, 0), glm::vec3(1, 10, 1), std::string(), false, Object::Type::Block));
	masterList.push_back(std::make_shared<Object>(glm::vec3(-7, 3, 0), glm::vec3(1, 10, 1), std::string(), false, Object::Type::Block));
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Frame action order:
		//  1.) Remove dead objects
		//  2.) Perform collision detection and response
		//  3.) Respond to user input
		//  4.) Perform "Update" function
		//  5.) Draw

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

		if(_pushLeft)
		{
			//player->Vel(player->Vel() + glm::vec3(-1, 0, 0));
			player->MoveLeft();
			//_pushLeft = false;
		}
		if(_pushRight)
		{
			//player->Vel(player->Vel() + glm::vec3(1, 0, 0));
			player->MoveRight();
			//_pushRight = false;
		}
		if(_jump)
		{
			//player->Vel(player->Vel() + glm::vec3(0, 1, 0));
			player->Jump();
			_jump = false;
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