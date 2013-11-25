#include "Bullet.h"

Bullet::Bullet(const glm::vec3& pos, const glm::vec3& vel, const std::string& texPath, const Object* owner, const glm::vec3& size) :
	Object(pos, size, texPath, false, Type::Bullet), _owner(owner)
{
	_vel = vel;
}

void Bullet::HandleCollision(Object* other)
{
	if(other->Type() != Object::Type::Bullet)
		_isAlive = false;
}