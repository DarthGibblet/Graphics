#include "Bullet.h"

Bullet::Bullet(const glm::vec3& pos, const glm::vec3& vel, const std::string& textPath, const Object* owner, const glm::vec3& size) :
	Object(pos, size, textPath, false, Type::Bullet), _ownerType(owner ? owner->Type() : Object::Type::Bullet), _minX(0), _maxX(0), _minY(0), _maxY(0)
{
	Vel(vel);
}

void Bullet::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList)
{
	if(Pos().x < _minX || Pos().x > _maxX || Pos().y < _minY || Pos().y > _maxY)
		IsAlive(false);

	Object::Update(secondsSinceLastUpdate, objList);
}

void Bullet::HandleCollision(Object* other)
{
	if(other->Type() != Object::Type::Generic && other->Type() != OwnerType())
		IsAlive(false);
}

Object::Type::E Bullet::OwnerType() const
{
	return _ownerType;
}

void Bullet::SetBounds(const double& minX, const double& maxX, const double& minY, const double& maxY)
{
	_minX = minX;
	_maxX = maxX;
	_minY = minY;
	_maxY = maxY;
}