#pragma once

#include <string>

extern const double GRAVITY_STRENGTH; //Strength of gravity on object (how fast they accellerate)
extern const double MAX_JUMP_HOLD_DURATION; //Maximum number of seconds holding the jump button is meaningful
extern const double BASE_JUMP_STRENGTH; //Base velocity upward when jumping
extern const double BULLET_SPEED; //Default velocity of bullets when fired
extern const double MAX_PLAYER_WALKING_SPEED; //Fasted a player can go while just walking in one direction

extern const int STENCIL_BUFFER_COLLISION_DETECTION_MASK; //Needs 1 bit of space

extern const char* RESOURCE_DIR_PATH; //Path to the directory that holds out resources
extern const char* SAVE_FILE_DIR_PATH; //Path to the directory that holds save files

std::string GetEnvName(const unsigned int& envId);
