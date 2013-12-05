#include "Bullet.h"

Bullet::Bullet(const glm::vec3& pos, const glm::vec3& vel, const std::string& texPath, const Object* owner, const glm::vec3& size) :
	Object(pos, size, texPath, false, Type::Bullet), _owner(owner), _minX(0), _maxX(0), _minY(0), _maxY(0)
{
	_vel = vel;
}

void Bullet::Update(const double& secondsSinceLastUpdate)
{
	if(_pos.x < _minX || _pos.x > _maxX || _pos.y < _minY || _pos.y > _maxY)
		_isAlive = false;

	Object::Update(secondsSinceLastUpdate);
}

void Bullet::HandleCollision(Object* other)
{
	if(other->Type() != Object::Type::Bullet)
		_isAlive = false;
}

void Bullet::SetBounds(const double& minX, const double& maxX, const double& minY, const double& maxY)
{
	_minX = minX;
	_maxX = maxX;
	_minY = minY;
	_maxY = maxY;
}