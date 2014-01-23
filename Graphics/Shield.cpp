#include "Shield.h"

Shield::Shield(const Object* owner): Bullet(glm::vec3(), glm::vec3(), "..\\resources\\Shield.dds", owner), _owner(owner)
{
	_type = Object::Type::Bullet;
	Update(0, std::vector<std::shared_ptr<Object>>());
}

void Shield::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList)
{
	Vel(_owner->Vel());
	_pos = _owner->Pos();
	_pos.x += _facingBackwards ? -0.5f : 0.5f;
	_size = _owner->Size();
}

void Shield::HandleCollision(Object* other)
{
}