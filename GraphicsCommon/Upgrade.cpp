#include "Upgrade.h"

Upgrade::Upgrade(const Upgrade::Type::E& type, const Object::Core& core) :
	Object(core), _power(type)
{
	switch(type)
	{
	case Upgrade::Type::WALL_JUMP:
		Text("..\\resources\\WallJump.dds");
		break;
	case Upgrade::Type::DOUBLE_JUMP:
		Text("..\\resources\\DoubleJump.dds");
		break;
	}
}

Upgrade::Upgrade(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, Upgrade::Type::E power) : 
	Object(pos, size, textPath, false, Object::Type::Upgrade), _power(power)
{
}

void Upgrade::HandleCollision(Object* other)
{
	if(other->Type() == Object::Type::Player)
		IsAlive(false);
}

Upgrade::Type::E Upgrade::Power()
{
	return _power;
}