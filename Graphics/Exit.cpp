#include "Exit.h"

Exit::Exit(const Object::Core& core, const std::string& newEnvName, const uint32_t& newEnvEntranceId, const env_change_func_t& envChange) : Object(core),
	_newEnvName(newEnvName), _newEnvEntranceId(newEnvEntranceId), _envChange(envChange)
{
}

void Exit::Draw()
{
}

void Exit::HandleCollision(Object* other)
{
	Object::HandleCollision(other);

	switch(other->Type())
	{
	case Object::Type::Player:
		_envChange(std::ref(_newEnvName), std::ref(_newEnvEntranceId));
		break;
	}
}

bool Exit::UsePreciseCollisions()
{
	return false;
}