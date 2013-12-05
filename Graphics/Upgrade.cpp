#include "Upgrade.h"

Upgrade::Upgrade(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, Upgrade::Type::E power) : 
	Object(pos, size, textPath, false, Object::Type::Upgrade), _power(power)
{
}

void Upgrade::HandleCollision(Object* other)
{
	if(other->Type() == Object::Type::Player)
		_isAlive = false;
}

Upgrade::Type::E Upgrade::Power()
{
	return _power;
}