#include "Constants.h"

#include <vector>

const double GRAVITY_STRENGTH = 10;
const double MAX_JUMP_HOLD_DURATION = 0.4;
const double BASE_JUMP_STRENGTH = 6;
const double BULLET_SPEED = 7;
const double MAX_PLAYER_WALKING_SPEED = 5;

const int STENCIL_BUFFER_COLLISION_DETECTION_MASK = 1;

const char* RESOURCE_DIR_PATH = "..\\resources\\";
const char* SAFE_FILE_DIR_PATH = "..\\saves\\";

std::string GetEnvName(const unsigned int& endId)
{
	static std::vector<std::string> conv_vector;
	static bool initialized = false;
	if(!initialized)
	{
		conv_vector.resize(2);
		conv_vector[0] = "start";
		conv_vector[1] = "one_zero";
		initialized = true;
	}

	if(endId >= conv_vector.size())
		return "";
	return conv_vector[endId];
}
