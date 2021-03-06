#include "Texture.h"
#include "Shader.h"
#include "Object.h"
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Upgrade.h"
#include "Camera.h"
#include "Quadtree.h"
#include "SaveFile.h"
#include "Environment.h"

#include <iostream>

#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

bool _useQuadtree = true;
bool _drawQuadtreeGraph = false;
bool _pushLeft = false;
bool _pushRight = false;
bool _save = false;
bool _jump = false, _releaseJump = false;
bool _crouchHold = false, _crouchRelease = false;;
bool _fire = false;
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

void Save()
{
	_save = true;
}

void JumpHold()
{
	_jump = true;
}

void JumpRelease()
{
	_releaseJump = true;
}

void CrouchHold()
{
	_crouchHold = true;
}

void CrouchRelease()
{
	_crouchRelease = true;
}

void Fire()
{
	_fire = true;
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
			_keyDownActions[GLFW_KEY_LEFT] = &PushLeft;
			_keyUpActions[GLFW_KEY_LEFT] = &StopLeft;
			_keyDownActions[GLFW_KEY_A] = &PushLeft;
			_keyUpActions[GLFW_KEY_A] = &StopLeft;
			_keyDownActions[GLFW_KEY_RIGHT] = &PushRight;
			_keyUpActions[GLFW_KEY_RIGHT] = &StopRight;
			_keyDownActions[GLFW_KEY_D] = &PushRight;
			_keyUpActions[GLFW_KEY_D] = &StopRight;
			_keyDownActions[GLFW_KEY_DOWN] = &CrouchHold;
			_keyUpActions[GLFW_KEY_DOWN] = &CrouchRelease;
			_keyDownActions[GLFW_KEY_S] = &Save;
			_keyDownActions[GLFW_KEY_SPACE] = &JumpHold;
			_keyUpActions[GLFW_KEY_SPACE] = &JumpRelease;
			_keyDownActions[GLFW_KEY_F] = &Fire;
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

	SaveFile save("..\\saves\\autosave.dat");
	uint32_t upgradeMask = 0;
	std::string envName = "start";
	uint32_t envEntranceId = 0;
	save.Read(upgradeMask, envName, envEntranceId);

	Environment curEnv(envName, envEntranceId);

	auto player = std::make_shared<Player>(upgradeMask);

	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	double ratio = (double)frameBufferHeight / frameBufferWidth;
	auto cam = std::make_shared<Camera>(10, ratio);
	cam->Teather(player.get());
	
	std::string newEnvName;
	uint32_t newEnvEntrance = 0;
	auto prepEnvChange = [&newEnvName, &newEnvEntrance](const std::string& name, const uint32_t& entranceId)
	{
		newEnvName = name;
		newEnvEntrance = entranceId;
	};
	vector<std::shared_ptr<Object>> masterList;
	curEnv.Read(masterList, player, cam, prepEnvChange);

	//for(int i=0;i<2000;++i)
	//{
	//	double randx = double(rand() % int(ZONE_MAX_X * 100 * 2) - (ZONE_MAX_X * 100) ) / 100;
	//	double randy = double(rand() % int(ZONE_MAX_Y * 100 * 2) - (ZONE_MAX_Y * 100) ) / 100;
	//	double randVelx = double(rand() % 40 - 20) / 20;
	//	double randVely = double(rand() % 40 - 20) / 20;
	//	std::shared_ptr<Bullet> newBullet = std::make_shared<Bullet>(glm::vec3(randx, randy, 0), glm::vec3(0, 0, 0), "..\\resources\\Bullet.dds", player.get());
	//	newBullet->Vel(glm::vec3(randVelx, randVely, 0));
	//	newBullet->SetBounds(-ZONE_MAX_X, ZONE_MAX_X, -ZONE_MAX_Y, ZONE_MAX_Y);
	//	masterList.push_back(newBullet);
	//}

	double lastTime = glfwGetTime(), framerateStartTime = lastTime;

	int frameCount = 0;

	while (!glfwWindowShouldClose(window))
	{
		double curTime = glfwGetTime();
		double timeSinceLastFrame = curTime - lastTime;
		lastTime = curTime;

		//Really quick hack to get rid of those pesky weird case frames (like window resizing/moving, pausing in a debugger, things like that)
		if(timeSinceLastFrame > 1)
			continue;

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
		//  3.) Perform "Update" function
		//  4.) Respond to user input
		//  5.) Draw

		masterList = std::vector<std::shared_ptr<Object>>(std::begin(masterList), std::remove_if(std::begin(masterList), std::end(masterList), [](std::shared_ptr<Object> obj) -> bool
		{
			return !obj->IsAlive();
		}));

		if(_useQuadtree)
		{
			//TODO*** - Have logic to maintain a constant QuadTree object between frames and only re-insert the objects that have moved since the last frame
			Quadtree objCollection(glm::vec3(0, 0, 0), curEnv.MaxX() * 2, curEnv.MaxY() * 2);
			std::for_each(std::begin(masterList), std::end(masterList), [&objCollection](decltype(*std::begin(masterList)) obj)
			{
				objCollection.Insert(obj.get());
			});
			objCollection.Update(timeSinceLastFrame, masterList);
			if(_drawQuadtreeGraph)
				objCollection.Draw();
		}
		else
		{
			foreach(masterList, std::bind(&Object::Update, std::placeholders::_1, timeSinceLastFrame, ref(masterList)));

			for(auto iObj = std::begin(masterList); iObj < std::end(masterList); ++iObj)
			{
				for(auto jObj = iObj + 1; jObj < std::end(masterList); ++jObj)
				{
					if((*iObj)->DoesCollide(*jObj))
					{
						(*iObj)->HandleCollision(*jObj);
						(*jObj)->HandleCollision(*iObj);
					}
				}
			}
		}

		if(_pushLeft)
		{
			player->MoveLeft();
		}
		if(_pushRight)
		{
			player->MoveRight();
		}
		if(_jump)
		{
			player->JumpHold();
			_jump = false;
		}
		if(_releaseJump)
		{
			player->JumpRelease();
			_releaseJump = false;
		}
		if(_crouchHold)
		{
			player->CrouchHold();
			_crouchHold = false;
		}
		if(_crouchRelease)
		{
			player->CrouchRelease();
			_crouchRelease = false;
		}
		if(_fire)
		{
			auto newBullet = player->Fire();
			if(newBullet)
			{
				newBullet->SetBounds(-curEnv.MaxX(), curEnv.MaxX(), -curEnv.MaxY(), curEnv.MaxY());
				masterList.push_back(newBullet);
				_fire = false;
			}
		}
		if(_save)
		{
			bool saveRes = save.Write(player->GetUpgradeMask(), curEnv.Name(), curEnv.EntranceId());
			if(saveRes)
				cout <<"Progress saved to file" <<endl;
			else
				cout <<"Error saving progress" <<endl;
			_save = false;
		}

		foreach(masterList, std::bind(&Object::Draw, std::placeholders::_1));

		//If there was an environment change, read the new environment file
		if(!newEnvName.empty())
		{
			curEnv = Environment(newEnvName, newEnvEntrance);
			curEnv.Read(masterList, player, cam, prepEnvChange);
			newEnvName.clear();
		}

		if(!player->IsAlive())
			_shouldClose = true;

		glfwSwapBuffers(window);
		glfwPollEvents();

		if(_shouldClose)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

	return 0;
}